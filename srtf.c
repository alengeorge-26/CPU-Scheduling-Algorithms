#include<stdio.h>
#include<string.h>

struct process
{
    char id[10];
    int AT,BT,WT,TAT,RT,STAT;
}P[10];

struct done
{
    char id[10];
    int ET,CT;
}D[50];

void presjf(int);
void sort(int);

int main()
{
    int n,i=0;

    printf("\nEnter the number of process : ");
    scanf("%d",&n);

    for (i = 0; i < n; i++)
    {
        printf("\nPROCESS %d\n",i+1);
         
        printf("Enter the Process ID : ");
        scanf("%s",P[i].id);

        printf("Enter the Arrival Time : ");
        scanf("%d",&P[i].AT);

        printf("Enter the Burst Time : ");
        scanf("%d",&P[i].BT);

        P[i].RT=P[i].BT;
    }

    presjf(n);
}

void presjf(int n)
{
    int TT=0,count=0,k=0,i=0,min=0;
    float TAWT=0.0,TATAT=0.0;

    while(count<n)
    {
        sort(n);

        i=count;
        min=count;

        if(TT<P[i].AT)
        {
            strcpy(D[k].id,"IDLE");
            D[k].ET=TT;
            D[k].CT=P[i].AT;
            TT=P[i].AT;
            k++;
            continue;
        }

        while(i<n)
        {
            if(P[i].RT<P[min].RT && P[i].AT<=TT)
            {
                min=i;
            }
            i++;
        }

        strcpy(D[k].id,P[min].id);
        D[k].ET=TT;
        TT++;
        D[k].CT=TT;

        P[min].RT--;
        k++;

        if(P[min].RT==0)
        {
            P[min].STAT=1;
            P[min].TAT=TT-P[min].AT;
            P[min].WT=P[min].TAT-P[min].BT;
            count++;
        }
    }

    for(i=0;i<n;i++)
    {
        TAWT=TAWT+P[i].WT;
        TATAT=TATAT+P[i].TAT;
    }

    TAWT=TAWT/n;
    TATAT=TATAT/n;

    printf("\n\nGANTT CHART ");
    printf("\n\t-------------------------------------------------------------------------------------------------------\n\t");
    for(i=0;i<k;i++)
    {
        printf("|");
        printf("%s\t",D[i].id);
    }
    printf("|");
    printf("\n\t-------------------------------------------------------------------------------------------------------\n\t");
    
    for(i=0;i<k;i++)
    {
        printf("%d\t",D[i].ET);
    }
    printf("%d\t\n",D[k-1].CT);

    printf("\nAVERAGE WAITING TIME : %f",TAWT);
    printf("\nAVERAGE TURNAROUND TIME : %f\n",TATAT);
}

void sort(int n)
{
    int i,j;
    struct process temp;

    for(i=1;i<n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(P[j+1].STAT==1 && P[j].STAT==0)
            {
                temp=P[j];
                P[j]=P[j+1];
                P[j+1]=temp;
            }
        }
    }
}