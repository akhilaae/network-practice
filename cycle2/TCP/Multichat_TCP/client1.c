#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
void* server_communication(void* sock){
    int sockid=*((int*)sock);
    while(1){
        char data[1024];
        bzero(data,1024);
        int rec=recv(sockid,data,1024,0);
        data[rec]='\0';
        printf("Broadcast : %s\n",data);
    }
}
void main(){
    int port=5454;
    char* ip="127.0.0.1";
    char buffer[1024];
    int sock=socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr(ip);
    socklen_t addr_size=sizeof(addr);
    connect(sock,(struct sockaddr*)&addr,sizeof(addr));
    printf("All set!\n");
    pthread_t thread;
    pthread_create(&thread,NULL,server_communication,(void*)&sock);
    while(1){
        bzero(buffer,1024);
        scanf("%s",buffer);
        if((strcmp(buffer,"SEND"))==0){
            send(sock,buffer,1024,0);
            bzero(buffer,1024);
            scanf("%s",buffer);
            send(sock,buffer,1024,0);
            bzero(buffer,1024);
            scanf("%s",buffer);
            send(sock,buffer,1024,0);
        }
    }
}