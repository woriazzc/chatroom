#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

using namespace std;

#define MAXEVENTS 200

char buf[105];
int epfd;

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage: ./server 5005\n");
    return -1;
  }
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ser_addr;
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_port = htons(atoi(argv[1]));
  ser_addr.sin_addr.s_addr = INADDR_ANY;
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
          struct sockaddr_in* addr_in = (struct sockaddr_in *)&addr;
          printf("Client %s(%d) connected.\n", inet_ntoa(addr_in->sin_addr), clientfd);
        }
        else if(events[i].events & EPOLLIN){
          memset(buf, 0, sizeof(buf));
          int clientfd = events[i].data.fd;
          if(read(clientfd, buf, sizeof(buf)) <= 0){
            printf("Client %d disconnected.\n", clientfd);
            memset(&ev, 0, sizeof(ev));
            ev.data.fd = clientfd;
            ev.events = EPOLLIN;
            epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, &ev);
            close(clientfd);
            continue;
          }
          printf("Client %d: %s\n", clientfd, buf);
          write(clientfd, buf, strlen(buf));
        }
      }
    }
  }
  close(epfd);
  return 0;
}