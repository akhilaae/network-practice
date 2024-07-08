#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

void main(){
    srand(time(0));
    char* ip="127.0.0.1";
    int port=5454;
    struct sockaddr_in server_addr,client_addr;
    int sock,bind_val;
    char buffer[1024];
    socklen_t addr_size;
    sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        printf("Socket creation failed!\n");
        exit(1);
    }
    printf("Server socket successfully created!\n");
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip);
    bind_val=bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(bind_val<0){
        printf("Binding failed!\n");
        exit(1);
    }
    printf("Binded succesfully!\n");
    int x=0;
    while (1){
        addr_size=sizeof(client_addr);
        bzero(buffer,1024);
        recvfrom(sock,buffer,1024,0,(struct sockaddr*)&client_addr,&addr_size);
        if(atoi(buffer)==x){
            printf("Duplicate : Packet %s\n",buffer);
        }
        else{
            printf("Recieved :  Packet %s\n",buffer);
        }
        x=atoi(buffer);
        sleep(1);
        if(rand()%2==0){
            sendto(sock,buffer,1024,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
            printf("Acknowledment sent : Packet %s\n",buffer);
        }
    }
}

