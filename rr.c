#include<stdio.h>
#include<string.h>

struct process
{
    int id;
    int AT,BT,WT,TAT,RT,STAT;
}P[10];

struct done
{
    int id;
    int ET,CT;
}D[50];

int queue[100];
int front=-1,rear=-1;


void rr(int,int);
void sort(int);
void enqueue(int);
int dequeue();
int indexof(int,int);
int present(int);

int main()
{
    int n,i=0,q;

    printf("\nEnter the number of process : ");
    scanf("%d",&n);

    printf("\nEnter the time quantum : ");
    scanf("%d",&q);

    for (i = 0; i < n; i++)
    {
        printf("\nPROCESS %d\n",i+1);
         
        printf("Enter the Process ID : ");
        scanf("%d",&P[i].id);

        printf("Enter the Arrival Time : ");
        scanf("%d",&P[i].AT);

        printf("Enter the Burst Time : ");
        scanf("%d",&P[i].BT);

        P[i].RT=P[i].BT;
    }

    rr(n,q);
}

void rr(int n,int q)
{
    int TT=0,count=0,k=0,i=0,x,flag=0;
    float TAWT=0.0,TATAT=0.0;

    enqueue(P[0].id);

    while(count<n)
    {
        sort(n);

        if(front==-1 && rear==-1)
        {
            D[k].id=0;
            D[k].ET=TT;
            enqueue(P[count].id);
            D[k].CT=P[count].AT;
            TT=P[count].AT;
            k++;
            continue;
        }

        i=indexof(dequeue(),n);
        D[k].ET=TT; 

        if(P[i].RT<=q)
        {
            TT=TT+P[i].RT;
            P[i].RT=0;
            P[i].STAT=1;
            P[i].TAT=TT-P[i].AT;
            count++; 
        }
        else
        {
            TT=TT+q;
            P[i].RT=P[i].RT-q;
        }

        for(x=count+1;x<n;x++)
        {
            if(!(present(P[x].id)) && P[x].AT<=TT && P[x].id!=P[i].id)
                enqueue(P[x].id);
        }

        if(P[i].STAT==0)
            enqueue(P[i].id);

        D[k].id=P[i].id;
        D[k].CT=TT;
        k++;       
    }

    for(i=0;i<n;i++)
    {
        P[i].WT=P[i].TAT-P[i].BT;
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
        printf("%d\t",D[i].id);
    }
    printf(" |");
    printf("\n\t-------------------------------------------------------------------------------------------------------\n\t");
    
    for(i=0;i<k;i++)
    {
        printf("%d\t",D[i].ET);
    }
    printf("%d\t\n",D[k-1].CT);

    printf("\nAVERAGE WAITING TIME : %f",TAWT);
    printf("\nAVERAGE TURNAROUND TIME : %f\n",TATAT);
}

void enqueue(int x)
{
    if(front==-1 && rear==-1)
        front++;
    rear++;
    queue[rear]=x;
}

int dequeue()
{
    int x;
    x=queue[front];
    if(front==rear)
    {
        front=-1;
        rear=-1;
    }
    else
        front++;
    return x;
}

int indexof(int x,int n)
{
    for(int i=0;i<n;i++)
    {
        if(P[i].id==x)
            return i;
    }
}

int present(int x)
{
    for(int i=front;i<=rear;i++)
    {
        if(queue[i]==x)
            return 1;
    }
    return 0;
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