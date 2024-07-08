#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define timeoutval 5
void main(){
    char* ip="127.0.0.1";
    int port=5454;
    struct sockaddr_in client_addr;
    int sock,connect_val;
    char buffer[1024];
    socklen_t addr_size;
    sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        printf("Socket creation failed!\n");
        exit(1);
    }
    printf("Server socket successfully created!\n");
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(port);
    client_addr.sin_addr.s_addr=inet_addr(ip);
    connect_val=connect(sock,(struct sockaddr*)&client_addr,sizeof(client_addr));
    if(connect_val<0){
        printf("Connection failed!\n");
        exit(1);
    }
    printf("COnnection succesful\n");
    int packetno=1;
    while(packetno<5){
        addr_size=sizeof(client_addr);
        bzero(buffer,1024);
        sprintf(buffer,"%d",packetno);
        printf("Sent : Packet %s\n",buffer);
        sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,sizeof(client_addr));

        struct timeval timeout;
        timeout.tv_sec=timeoutval;
        timeout.tv_usec=0;

        if(setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout))<0){
            printf("Error\n");
        }
        else{
            bzero(buffer,1024);
            int rec=recvfrom(sock,buffer,1024,0,(struct sockaddr*)&client_addr,&addr_size);
            if(rec<0){
                printf("Timeout!! Resending Packet %s to server!\n ",buffer);
            }
            else{
                printf("Acknowelegment Recieved : Packet %s\n",buffer);
                packetno++;
            }
        }
        sleep(1);
    }
}