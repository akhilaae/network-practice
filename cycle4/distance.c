#include <stdio.h>
#include <stdlib.h>
void main(){
    int n,i,j,k;
    printf("Enter no of routers :");
    scanf("%d",&n);
    int cost[n][n];
    printf("Enter cost matrix : ");
    for (i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&cost[i][j]);
        }
    }
    int f;
    do{
        f=0;
        for (i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                    if(cost[i][j]>cost[i][k]+cost[k][j]){
                        cost[i][j]=cost[i][k]+cost[k][j];
                        f=1;
                    }
                }
            }
        }

    }while (f!=0);
    printf("Table : \n");
    for(i=0;i<n;i++){
        printf("%c ",i+65);
    }
    printf("\n");
    for(i=0;i<n;i++){
        printf("%c ",i+65);
        for(j=0;j<n;j++){
            printf("%d ",cost[i][j]);
        }
        printf("\n");
    }
}