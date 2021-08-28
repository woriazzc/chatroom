#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>

using namespace std;

#define CLIENT_PORT 9000
#define GROUP "239.0.0.2"

char buff[105];
char con_msg[105];

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: ./client 127.0.0.1 5005\n");
        return -1;
    }

    // local socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // udp socket
    int udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(CLIENT_PORT);
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(udpfd, (struct sockaddr *)&client_addr, sizeof(client_addr));

    // set multicast
    struct ip_mreqn group;
    memset(&group, 0, sizeof(group));
    group.imr_address.s_addr = htonl(INADDR_ANY);
    group.imr_multiaddr.s_addr = inet_addr(GROUP);
    group.imr_ifindex = if_nametoindex("eth0");
    setsockopt(udpfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));

    // server socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0){
        printf("Connect Error.\n");
        return -1;
    }
    while(1){
        // memset(buff, 0, sizeof(buff));
        // printf("Input: ");
        // scanf("%s", buff);
        // if(write(sockfd, buff, strlen(buff)) == -1){
        //     printf("Write Error.\n");
        //     return -1;
        // }
        // if(read(sockfd, buff, sizeof(buff)) == -1){
        //     printf("Read Error.\n");
        //     return -1;
        // }
        // printf("Server: %s\n", buff);
        memset(con_msg, 0, sizeof(con_msg));
        if(recvfrom(udpfd, con_msg, sizeof(con_msg), 0, NULL, 0) == -1){
            printf("UDP ERROR.\n");
        }
        printf("%s\n", con_msg);
    }
    return 0;
}