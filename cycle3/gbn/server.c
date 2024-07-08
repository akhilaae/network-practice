#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define packetno 5
void main(){
    char* ip="127.0.0.1";
    int port=5454;
    struct sockaddr_in server_addr,client_addr;
    int sock,bind_val,recd[10];
    socklen_t addr_size;
    char buffer[1024];
    sock=socket(AF_INET,SOCK_DGRAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip);
    bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("All set!\n");
    for(int i=0;i<packetno;i++){
        recd[i]=-1;
    }
    int b;
    while(1){
        bzero(buffer,1024);
        addr_size=sizeof(server_addr);
        recvfrom(sock,buffer,1024,0,(struct sockaddr*)&server_addr,&addr_size);
        b=atoi(buffer);
        if(recd[b]==b){
            printf("Server : Recieved : Packet %s : Duplicate\n",buffer);
        }
        else{
            printf("Server : Recieved : Packet %s\n",buffer);
            recd[b]=b;
        }
        sleep(1);
        if(rand()%2==0){
            printf("Server : Acknowledgement sent : Packet %s\n",buffer);
            sendto(sock,buffer,1024,0,(struct sockaddr*)&server_addr,sizeof(server_addr));
        }
    }
    close(sock);
}