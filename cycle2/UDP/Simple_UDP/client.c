#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void main(){
    char* ip="127.0.0.1";
    int port=5454;
    int clientsock;
    struct sockaddr_in client_addr;
    socklen_t addr_size;
    char buffer[1024];
    clientsock=socket(AF_INET,SOCK_DGRAM,0);
    if(clientsock<0){
        printf("SOcket creation failed for client!\n");
        exit(1);
    }
    printf("Client socket created!\n");
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(port);
    client_addr.sin_addr.s_addr=inet_addr(ip);
    printf("Server-client connected!\n");
    addr_size=sizeof(client_addr);
    bzero(buffer,1024);
    strcpy(buffer,"HI - from client");
    sendto(clientsock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
    bzero(buffer,0);
    recvfrom(clientsock,buffer,1024,0,(struct sockaddr*)&client_addr,&addr_size);
    printf("Server : %s\n",buffer);
    close(clientsock);
}