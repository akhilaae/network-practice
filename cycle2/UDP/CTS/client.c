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
    int sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    int num=1;
    time_t start_time,current_time,rtt;
    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(S_PORT);
    server_addr.sin_addr.s_addr=inet_addr(IP);

    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(C_PORT);
    client_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    socklen_t len=sizeof(client_addr);

    printf("Client is running on %s:%d\n",IP,C_PORT);

    start_time=time(NULL);
    sendto(sock,&num,sizeof(num),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
    recvfrom(sock,&current_time,sizeof(current_time),0,(struct sockaddr*)&client_addr,&len);
    rtt=time(NULL)-start_time;
    current_time+=rtt/2;
    printf("Server current time : %s\n",ctime(&current_time));
}