#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define packetnos 5
#define windowsize 3
#define timeoutval 5
void sendpacketsinwindow(int sock,int packets[],struct sockaddr_in server_addr,int windowstart,int windowend){
    while(windowstart<windowend){
        char buffer[1024];
        bzero(buffer,1024);
        sprintf(buffer,"%d",packets[windowstart]);
        printf("Client : Sent : Packet %s\n",buffer);
        sendto(sock,buffer,1024,0,(struct sockaddr*)&server_addr,sizeof(server_addr));
        windowstart++;
    }
}
void main(){
    char* ip="127.0.0.1";
    int port=5454;
    struct sockaddr_in client_addr;
    int sock,bind_val,windowstart,windowend;
    socklen_t addr_size;
    char buffer[1024];
    sock=socket(AF_INET,SOCK_DGRAM,0);
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(port);
    client_addr.sin_addr.s_addr=inet_addr(ip);
    bind(sock,(struct sockaddr*)&client_addr,sizeof(client_addr));
    printf("All set!\n");
    int packets[packetnos];
    for(int i=0;i<packetnos;i++){
        packets[i]=i+1;
    }
    windowstart=0;
    windowend=windowstart+windowsize;

    sendpacketsinwindow(sock,packets,client_addr,windowstart,windowend);
    int flag=1;
    while(windowstart!=windowend){
        bzero(buffer,1024);
        addr_size=sizeof(client_addr);
        struct timeval timeout;
        timeout.tv_sec=timeoutval;
        timeout.tv_usec=0;
        if(setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout))<0){
            printf("Error!\n");
        }
        else{
            int rec=recvfrom(sock,buffer,1024,0,(struct sockaddr*)&client_addr,&addr_size);
            if(rec<0){
                printf("Timeout : Sending window again!\n");
                sendpacketsinwindow(sock,packets,client_addr,windowstart,windowend);
            }
            else{
                printf("Recieved acknowledgment for packet %s\n",buffer);
                if(atoi(buffer)!=packets[windowstart]){
                    printf("Wrong acknowledgment recieved! Sending window again!\n");
                    sendpacketsinwindow(sock,packets,client_addr,windowstart,windowend);
                }
                else{
                    windowstart++;
                    if(windowend<packetnos){
                        windowend++;
                    }
                    if(windowstart<windowend){
                        if(flag==1){
                            bzero(buffer,1024);
                            sprintf(buffer,"%d",packets[windowend-1]);
                            sendto(sock,buffer,1024,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
                            printf("Client : Sent : Packet %s\n",buffer);
                        }
                    }
                    if(windowend==packetnos){
                        flag=0;
                    }
                }
            }
        }
    }
    close(sock);
}