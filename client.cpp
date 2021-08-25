#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

char buff[105];
int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: ./client 127.0.0.1 5005\n");
        return -1;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0){
        printf("Connect Error.\n");
        return -1;
    }
    while(1){
        memset(buff, 0, sizeof(buff));
        printf("Input: ");
        scanf("%s", buff);
        if(write(sockfd, buff, strlen(buff)) == -1){
            printf("Write Error.\n");
            return -1;
        }
        if(read(sockfd, buff, sizeof(buff)) == -1){
            printf("Read Error.\n");
            return -1;
        }
        printf("Repeat: %s\n", buff);
    }
    return 0;
}