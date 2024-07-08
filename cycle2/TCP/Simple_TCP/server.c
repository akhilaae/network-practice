#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void main(){
    char* ip="127.0.0.1";
    int port = 5454;
    struct sockaddr_in server_addr,client_addr;
    int serversock,clientsock,bind_val;
    char buffer[1024];
    socklen_t addr_size;
    serversock=socket(AF_INET,SOCK_STREAM,0);
    if(serversock<0){
        printf("Socket not created!\n");
        exit(1);
    }
    printf("Socket created!\n");
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);
    bind_val=bind(serversock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(bind_val<0){
        printf("binding failed!\n");
        exit(1);
    }
    listen(serversock,10);
    printf("Listening...\n");
    while(1){
        addr_size=sizeof(client_addr);
        clientsock=accept(serversock,(struct sockaddr*)&client_addr,&addr_size);
        bzero(buffer,1024);
        recv(clientsock,buffer,1024,0);
        printf("Client : %s\n",buffer);
        bzero(buffer,1024);
        strcpy(buffer,"HI -  from server");
        send(clientsock,buffer,strlen(buffer),0);
        close(clientsock);
    }
    close(serversock);
}