#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define S_PORT 5454
#define C_PORT 5455
#define IP "127.0.0.1"
#define ERROR -1

void main(){
    int num;
    time_t current_time;
    int sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(S_PORT);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(C_PORT);
    server_addr.sin_addr.s_addr=inet_addr(IP);

    bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    socklen_t len;
    printf("Server is running on %s:%d\n",IP,S_PORT);
    while(1){
        len=sizeof(client_addr);
        recvfrom(sock,&num,sizeof(num),0,(struct sockaddr*)&client_addr,&len);
        current_time=time(NULL);
        printf("Client at %s:%d has requested for time : %s\n",IP,C_PORT,ctime(&current_time));
        sendto(sock,&current_time,sizeof(current_time),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
    }
}