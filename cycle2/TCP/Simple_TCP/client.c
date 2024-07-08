#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void main(){
    char* ip="127.0.0.1";
    int port=5454;
    int clientsock,connection;
    struct sockaddr_in client_addr;
    char buffer[1024];
    clientsock=socket(AF_INET,SOCK_STREAM,0);
    if(clientsock<0){
        printf("SOcket creation failed for client!\n");
        exit(1);
    }
    printf("Client socket created!\n");
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=port;
    client_addr.sin_addr.s_addr=inet_addr(ip);
    connection=connect(clientsock,(struct sockaddr*)&client_addr,sizeof(client_addr));
    if(connection<0){
        printf("Not connected!\n");
        exit(1);
    }
    printf("Server-client connected!\n");
    bzero(buffer,1024);
    strcpy(buffer,"HI - from client");
    send(clientsock,buffer,strlen(buffer),0);
    bzero(buffer,0);
    recv(clientsock,buffer,1024,0);
    printf("Server : %s\n",buffer);
    close(clientsock);
}