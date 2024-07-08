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
    int sock,bind_val;
    char buffer[1024];
    socklen_t addr_size;
    sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        printf("Socket not created!\n");
        exit(1);
    }
    printf("Socket created!\n");
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip);
    bind_val=bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(bind_val<0){
        printf("binding failed!\n");
        exit(1);
    }
    
    addr_size=sizeof(client_addr);
    bzero(buffer,1024);
    recvfrom(sock,buffer,1024,0,(struct sockaddr*)&client_addr,&addr_size);
    printf("Client : %s\n",buffer);
    bzero(buffer,1024);
    strcpy(buffer,"HI -  from server");
    sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
    close(sock);
}