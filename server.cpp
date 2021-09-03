#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <net/if.h>
#include <unordered_set>
#include "./utils/mysqlControler.h"
#include "./utils/utils.h"

using namespace std;

#define MAXEVENTS 200
#define GROUP "239.0.0.2"
#define CLIENT_PORT 9000
#define SERVER_PORT 6666

#define LOGIN "0"
#define CONN "1"
#define MESSAGE "2"
#define ENROLL "3"
#define DISCONN "4"
#define USRLST "5"

char buf[10005], usr[200], pwd[200], type[10], usrs[10005], usrid[20];
int epfd;
char login_msg[40], send_msg[20005];

unordered_set<int> usrlst;


int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage: ./server 5005\n");
    return -1;
  }
  
  mysqlControler con;

  // listen socket
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1; unsigned int len = sizeof(opt);
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, len);
  setsockopt(listenfd, SOL_SOCKET, SO_KEEPALIVE, &opt, len);
  struct sockaddr_in ser_addr;
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_port = htons(atoi(argv[1]));
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(listenfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) != 0){
    printf("Bind Error.\n");
    close(listenfd);
    return -1;
  }
  if(listen(listenfd, 5) != 0){
    printf("Listen Error.\n");
    close(listenfd);
    return -1;
  }


  // udp socket
  int udpfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in udp_addr;
  memset(&udp_addr, 0, sizeof(udp_addr));
  udp_addr.sin_family = AF_INET;
  udp_addr.sin_port = htons(SERVER_PORT);
  udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(udpfd, (struct sockaddr *)&udp_addr, sizeof(udp_addr));

  // set multicast
  struct ip_mreqn group;
  memset(&group, 0, sizeof(group));
  group.imr_address.s_addr = htonl(INADDR_ANY);
  group.imr_multiaddr.s_addr = inet_addr(GROUP);
  group.imr_ifindex = if_nametoindex("eth0");
  setsockopt(udpfd, IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));

  // multicast sockaddr
  struct sockaddr_in client_in;
  memset(&client_in, 0, sizeof(client_in));
  client_in.sin_family = AF_INET;
  client_in.sin_port = htons(CLIENT_PORT);
  client_in.sin_addr.s_addr = inet_addr(GROUP);


  if((epfd = epoll_create(1)) == -1){
    printf("Epoll Create Error.\n");
    return -1;
  }
  struct epoll_event ev;
  ev.data.fd = listenfd;
  ev.events = EPOLLIN;
  if((epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev)) != 0){
    printf("Epoll CTL Error.\n");
    return -1;
  }
  printf("Listening...\n");
  while(1){
    struct epoll_event events[MAXEVENTS];
    int evnum = epoll_wait(epfd, events, MAXEVENTS, -1);
    if(evnum == -1){
      printf("Epoll_wait Error.\n");
      break;
    }
    else if(evnum == 0){
      printf("Epoll_wait Timeout.\n");
      continue;
    }
    else{
      for (int i = 0; i < evnum; i++){
        if(events[i].data.fd == listenfd && (events[i].events & EPOLLIN)){
          // 新客户端连入
          struct sockaddr addr;
          int clientfd;
          socklen_t len = sizeof(addr);
          if((clientfd = accept(listenfd, &addr, &len)) == -1){
            printf("Accept Error.\n");
            continue;
          }
          memset(&ev, 0, sizeof(ev));
          ev.data.fd = clientfd;
          ev.events = EPOLLIN;
          epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev);
          // struct sockaddr_in* addr_in = (struct sockaddr_in *)&addr;
          // printf("Client %s(%d) connected.\n", inet_ntoa(addr_in->sin_addr), clientfd);
          // memset(send_msg, 0, sizeof(send_msg));
          // sprintf(send_msg, "Client %s(%d) connected.\n", inet_ntoa(addr_in->sin_addr), clientfd);
          // sendto(udpfd, send_msg, strlen(send_msg), 0, (struct sockaddr *)&client_in, sizeof(client_in));
        }
        else if(events[i].events & EPOLLIN){
          memset(buf, 0, sizeof(buf));
          int clientfd = events[i].data.fd;
          if(read(clientfd, buf, sizeof(buf)) <= 0){
            // printf("Client %d disconnected.\n", clientfd);
            // memset(send_msg, 0, sizeof(send_msg));
            // sprintf(send_msg, "Client %d disconnected.\n", clientfd);
            // sendto(udpfd, send_msg, strlen(send_msg), 0, (struct sockaddr *)&client_in, sizeof(client_in));
            memset(&ev, 0, sizeof(ev));
            ev.data.fd = clientfd;
            ev.events = EPOLLIN;
            epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
            close(clientfd);
            continue;
          }
          printf("%s\n", buf);
          memset(type, 0, sizeof(type));
          int p0 = 0;
          for (; buf[p0] != '\n'; p0++){
            type[p0] = buf[p0];
          }
          if(strcmp(type, LOGIN) == 0 || strcmp(type, ENROLL) == 0){
            memset(usr, 0, sizeof(usr));
            memset(pwd, 0, sizeof(pwd));
            int p1 = 0;
            p0++;
            for (; buf[p0] != '\n'; p0++){
              usr[p1++] = buf[p0];
            }
            p1 = 0;
            p0++;
            for (; buf[p0] && buf[p0] != '\n'; p0++){
              pwd[p1++] = buf[p0];
            }
            memset(login_msg, 0, sizeof(login_msg));
            if(strcmp(type, LOGIN) == 0){
              int uid = con.isValidUser(usr, pwd);
              if(usrlst.find(uid) != usrlst.end()){
                sprintf(login_msg, "%s\n-1", LOGIN);
                write(clientfd, login_msg, strlen(login_msg));
                continue;
              }
              if(uid != 0)
                usrlst.insert(uid);
              memset(usrid, 0, sizeof(usrid));
              itoa(uid, usrid);
              sprintf(login_msg, "%s\n%s", LOGIN, usrid);
            }
            else if(strcmp(type, ENROLL) == 0){
              int uid = con.insertUser(usr, pwd);
              if(uid != 0)
                usrlst.insert(uid);
              memset(usrid, 0, sizeof(usrid));
              itoa(uid, usrid);
              sprintf(login_msg, "%s\n%s", ENROLL, usrid);
            }
            write(clientfd, login_msg, strlen(login_msg));
          }
          else if(strcmp(type, CONN) == 0 || strcmp(type, DISCONN) == 0){
            memset(usrid, 0, sizeof(usrid));
            int p1 = 0;
            p0++;
            for (; buf[p0] != '\n'; p0++){
              usrid[p1++] = buf[p0];
            }
            if(strcmp(type, CONN) == 0)
              usrlst.insert(atoi(usrid));
            else
              usrlst.erase(atoi(usrid));
            char usrCnt[10] = {0};
            itoa((int)usrlst.size(), usrCnt);
            memset(usrs, 0, sizeof(usrs));
            for(auto u:usrlst){
              strcat(usrs, con.qryUserName(u));
              strcat(usrs, "\n");
            }
            memset(send_msg, 0, sizeof(send_msg));
            sprintf(send_msg, "%s\n%s\n%s", USRLST, usrCnt, usrs);
            // printf("%s\n", send_msg);
            sendto(udpfd, buf, strlen(buf), 0, (struct sockaddr *)&client_in, sizeof(client_in));
            sendto(udpfd, send_msg, strlen(send_msg), 0, (struct sockaddr *)&client_in, sizeof(client_in));
          }
          else{
            sendto(udpfd, buf, strlen(buf), 0, (struct sockaddr *)&client_in, sizeof(client_in));
          }
        }
      }
    }
  }
  close(epfd);
  close(listenfd);
  close(udpfd);
  return 0;
}