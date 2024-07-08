#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,i,j,addedcount=0,root,distAC,distBC;
    printf("No of nodes : ");
    scanf("%d",&n);
    int cost[n][n],added[n];
    printf("Enter cost amtrix : \n");
    for(i=0;i<n;i++){
        for (j=0;j<n;j++){
            scanf("%d",&cost[i][j]);
        }
    }
    for (int k=0;k<n;k++){
        root=k;
        for (i=0;i<n;i++){
            added[i]=0;
        }
        addedcount=0;
        added[root]=1;
        addedcount+=1;
        while(addedcount<n){
            int index;
            int min=__INT_MAX__;
            for(i=0;i<n;i++){
                if(added[i]!=1 && cost[root][i]!=-1 && cost[root][i]<min && root!=i){
                    index=i;
                    min=cost[root][i];
                }
            }
            added[index]=1;
            addedcount++;
            for(i=0;i<n;i++){
                if(added[i]==1)
                    continue;
                distAC=cost[root][i]==-1? __INT_MAX__:cost[root][i];
                distBC=cost[index][i]==-1? __INT_MAX__:cost[index][i];
                if(distBC+min<distAC && distBC!=__INT_MAX__)
                    cost[root][i]=distBC+min;
            }
        }
        printf("Routing table for %d as root : \n",root);
        for(i=0;i<n;i++){
            printf("%d\t%d\n",i,cost[root][i]);
        }
    }
    return 0;
}