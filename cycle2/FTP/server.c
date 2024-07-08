#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
    char* ip="127.0.0.1";
    int port=5454;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_size;
    int serversock,clientsock;
    char buffer[1024];
    serversock=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=port;
    server_addr.sin_addr.s_addr=inet_addr(ip);
    bind(serversock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(serversock,1024);
    addr_size=sizeof(client_addr);
    clientsock=accept(serversock,(struct sockaddr*)&client_addr,&addr_size);
    printf("All set!\n");
    char filename[1024];
    FILE* fptr;
    while(1){
        bzero(buffer,1024);
        recv(clientsock,buffer,1024,0);
        if(strcmp(buffer,"PUT")==0){
            bzero(buffer,1024);
            recv(clientsock,buffer,1024,0);
            strcpy(filename,buffer);
            bzero(buffer,1024);
            fptr=fopen(filename,"w");
            printf("Data written to file %s in server : \n",filename);
            while(1){
                recv(clientsock,buffer,1024,0);
                if(strcmp(buffer,"END$")==0){
                    break;
                }
                printf("%s\n",buffer);
                fprintf(fptr,"%s",buffer);
                bzero(buffer,1024);
            }
            fclose(fptr);
            printf("File %s written to server!\n",filename);
        }
        else if(strcmp(buffer,"GET")==0){
            bzero(buffer,1024);
            recv(clientsock,buffer,1024,0);
            strcpy(filename,buffer);
            bzero(buffer,1024);
            fptr=fopen(filename,"r");
            if(!fptr){
                printf("File does not exist\n");
                strcpy(buffer,"404");
                send(clientsock,buffer,1024,0);
            }
            else{
                while(!feof(fptr)){
                    fscanf(fptr,"%[^\n]",buffer);
                    send(clientsock,buffer,1024,0);
                    bzero(buffer,1024);
                }
                strcpy(buffer,"END$");
                send(clientsock,buffer,1024,0);
                bzero(buffer,1024);
                printf("File %s written to client!\n",filename);
            }
            fclose(fptr);
        }
        else if(strcmp(buffer,"BYE")==0){
            close(serversock);
            exit(0);
        }
    }
}