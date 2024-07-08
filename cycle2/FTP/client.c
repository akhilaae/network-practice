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
    struct sockaddr_in client_addr;
    int clientsock,choice;
    char buffer[1024];
    clientsock=socket(AF_INET,SOCK_STREAM,0);
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=port;
    client_addr.sin_addr.s_addr=inet_addr(ip);
    connect(clientsock,(struct sockaddr*)&client_addr,sizeof(client_addr));
    printf("All set!\n");
    char filename[1024];
    FILE* fptr;
    while(1){
        printf("Choode :\n1.Upload to server(PUT)\n2.Download to client(GET)\n3.Exit(BYE)\nEnter choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                bzero(buffer,1024);
                printf("Enter filename : ");
                scanf("%s",filename);
                fptr=fopen(filename,"r");
                if(!fptr){
                    printf("File does not exist\n");
                }
                else{
                    strcpy(buffer,"PUT");
                    send(clientsock,buffer,1024,0);
                    bzero(buffer,1024);
                    strcpy(buffer,filename);
                    send(clientsock,buffer,1024,0);
                    bzero(buffer,1024);
                    while(!feof(fptr)){
                        fscanf(fptr,"%[^\n]",buffer);
                        send(clientsock,buffer,1024,0);
                        bzero(buffer,1024);
                    }
                    strcpy(buffer,"END$");
                    send(clientsock,buffer,1024,0);
                    bzero(buffer,1024);
                    printf("File %s sent to server!\n",filename);
                }
                fclose(fptr);
                break;
            }
            case 2:{
                bzero(buffer,1024);
                strcpy(buffer,"GET");
                send(clientsock,buffer,1024,0);
                bzero(buffer,1024);
                printf("Enter filename : ");
                scanf("%s",filename);
                strcpy(buffer,filename);
                send(clientsock,buffer,1024,0);
                bzero(buffer,1024);
                recv(clientsock,buffer,1024,0);
                if(strcmp(buffer,"404")==0){
                    printf("No such file exists in the server!\n");
                }
                else{
                    fptr=fopen(filename,"w");
                    while(1){
                        recv(clientsock,buffer,1024,0);
                        if(strcmp(buffer,"END$")==0){
                            break;
                        }
                        printf("%s\n",buffer);
                        fprintf(fptr,"%s",buffer);
                        bzero(buffer,1024);
                    }
                    printf("File %s written in client!\n",filename);
                    fclose(fptr);
                }
                break;
            }
            case 3:{
                bzero(buffer,1024);
                strcpy(buffer,"BYE");
                send(clientsock,buffer,1024,0);
                close(clientsock);
                exit(0);
            }
        }
    }
}