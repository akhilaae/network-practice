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

typedef struct client{
    int index;
    int sock;
    struct sockaddr_in addr;
}client;

client clients[1024];
int clientcount=0;
pthread_t thread[1024];

void* client_communication(void* clientdetails){
    client* clientinfo=(client*)clientdetails;
    int index=clientinfo->index;
    int sock=clientinfo->sock;
    while(1){
        char buffer[1024];
        bzero(buffer,1024);
        int rec=recv(sock,buffer,1024,0);
        buffer[rec]='\0';
        if((strcmp(buffer,"SEND"))==0){
            bzero(buffer,1024);
            int rec=recv(sock,buffer,1024,0);
            buffer[rec]='\0';
            int id=atoi(buffer)-1;
            bzero(buffer,1024);
            rec=recv(sock,buffer,1024,0);
            buffer[rec]='\0';
            for(int i=0;i<clientcount;i++){
                if(id==i){
                    continue;
                }
                else{
                    send(clients[i].sock,buffer,1024,0);
                }
            }
        }
    }
}
void main(){
    int port=5454;
    char* ip="127.0.0.1";
    char buffer[1024];
    struct sockaddr_in server_addr,client_addr;
    int serversock=socket(PF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip);
    bind(serversock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(serversock,1024);
    printf("All set\n");
    while (1){
        socklen_t addr_size=sizeof(client_addr);
        clients[clientcount].sock=accept(serversock,(struct sockaddr*)&client_addr,&addr_size);
        pthread_create(&thread[clientcount],NULL,client_communication,(void*)&clients[clientcount]);
        clientcount++;
    }
    for(int i=0;i<clientcount;i++){
        pthread_join(thread[i],NULL);
    }
}