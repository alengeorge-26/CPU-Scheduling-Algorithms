#include<stdio.h>
#include<string.h>

struct process
{
    char id[10];
    int AT,BT,WT,TAT,PRIO,STAT;
}P[10];

struct done
{
    char id[10];
    int AT,CT;
}D[10];

void ps(int);
void sort(int);

int main()
{
    int n, i = 0;

    printf("\nEnter the number of process : ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nPROCESS %d\n",i+1);
         
        printf("Enter the Process ID : ");
        scanf("%s",P[i].id);

        printf("Enter the Arrival Time : ");
        scanf("%d",&P[i].AT);

        printf("Enter the Burst Time : ");
        scanf("%d",&P[i].BT);

        printf("Enter the Priority : ");
        scanf("%d",&P[i].PRIO);
    }

    ps(n);
}

void ps(int n)
{
    int TT=0,count=0,k=0,i,min;
    float TAWT=0.0,TATAT=0.0;

    while(count<n)
    {
        sort(n);

        i=count,min=count;

        if(TT < P[i].AT)
        {
            strcpy(D[k].id,"IDLE");
            D[k].AT=TT;
            D[k].CT=P[i].AT;
            TT=P[i].AT;
            k++;
            continue;
        }

        while(i<n)
        {
            if(P[i].PRIO<P[min].PRIO && P[i].AT<=TT)
            {
                min=i;
            }
            i++;
        }

        strcpy(D[k].id,P[min].id);
        D[k].AT=TT;
        D[k].CT=TT+P[min].BT;
        TT=TT+P[min].BT;

        P[min].TAT=TT-P[min].AT;
        P[min].WT=P[min].TAT-P[min].BT;
        P[min].STAT=1;

        TAWT=TAWT+P[min].WT;
        TATAT=TATAT+P[min].TAT;
        k++;
        count++;       
    }

    TAWT=TAWT/n;
    TATAT=TATAT/n;

    printf("\n\nGANTT CHART ");
    printf("\n\t--------------------------------------------------------------------\n\t");
    for(i=0;i<k;i++)
    {
        printf("|");
        printf("%s\t",D[i].id);
    }
    printf(" |");
    printf("\n\t--------------------------------------------------------------------\n\t");
    
    for(i=0;i<k;i++)
    {
        printf("%d\t",D[i].AT);
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