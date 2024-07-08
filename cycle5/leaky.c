#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define packetCount 3
int main(){
    srand(time(0));
    int packets[packetCount],i,rate,bucketSize,filled=0,time,op,clk;
    for(i=0;i<packetCount;++i){
        packets[i]=(rand()%6+1)*10;
        printf("%d",packets[i]);
    }
    printf("Enter rate : ");
    scanf("%d",&rate);
    printf("Enter bucketSize : ");
    scanf("%d",&bucketSize);

    i=0;
    while(i<packetCount || filled>0){
        if(i<packetCount){
            if(packets[i]+filled>bucketSize){
                printf("Overflow\n");
            }
            else{
                filled+=packets[i];
                printf("Packet %d enters bucket\n",packets[i]);
                printf("filled bucketsize : %d\n",filled);
            }
            ++i;
        }
        time=(rand()%4+1)*10;
        printf("Transmission time : %d\n",time);
        for (clk=10;clk<=time;clk+=10){
            sleep(1);
            if(filled){
                if(filled>rate){
                    op=rate;
                    filled-=rate;
                }
                else{
                    op=filled;
                    filled=0;
                }
                printf("Size of packet recieved : %d\n",op);
                printf("filled : %d\n",filled);
            }
            else{
                printf("Remaining time : %d\n",time-clk);
                printf("Done\n");
            }
        }
    }
}