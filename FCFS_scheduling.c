//CS21B1036
// R Anjana Narayan
#include<stdio.h>
#include<stdlib.h>

struct node // Queue structure
{
    int pid, at, bt, ct;
    struct node *next;
};

struct node *front=NULL;
struct node *rear=NULL;

struct info // Data
{
    int pid, at, bt;
};

void enqueue(int id,int at,int bt,int ct) // Adding data into the queue
{
    struct node *temp;
    temp=(struct node*)malloc(sizeof(struct node)); // Dynamic memory allocation
    temp->pid=id; // Adding values
    temp->at=at;
    temp->bt=bt;
    temp->ct=ct;
    temp->next=NULL;
    if((front==NULL) && (rear==NULL)) // If front and rear is pointed to NULL
        front=rear=temp;
    else
    {
        rear->next=temp;
        rear=temp;
    }
}

struct info dequeue()
{
    if(front==NULL) // Checking the overflow condition
    {
        printf("Queue underflow!\n");
        struct info ptr;
        ptr.pid=0; // Assigning every data to zero
        ptr.at=0;
        ptr.bt=0;
        return ptr;
    }
    else
    {
        struct node *temp=front;
        struct info ptr;
        ptr.pid=front->pid;
        ptr.at=front->at;
        ptr.bt=front->bt;
        front=front->next;
        free(temp);
        return ptr;
    }
}

int main()
{
    int n, i, p_id, at, bt, ct, tat, wt;
    float total_wt=0, total_tat=0;
    printf("Enter the total number of processes: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {  
        printf("Enter the process ID of process %d: ", i+1);
        scanf("%d", &p_id);
        printf("Enter the arrival time of process %d: ", i+1);
        scanf("%d", &at);
        printf("Enter the burst time of process %d: ", i+1);
        scanf("%d", &bt);
        if(i==0)
            ct=at;
        if(ct>=at)
            ct+=bt;
        else  // If there is any idle time in CPU
            ct=at+bt;
        enqueue(p_id,at,bt,ct);
    }
    struct node *temp;
    printf("P_id\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    if((front==NULL) && (rear==NULL))
        printf("Ready queue is empty\n");
    else
    {
        temp=front;
        while(front)
        {  
            tat=temp->ct-temp->at;
            wt=tat-temp->bt;
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",temp->pid,temp->at,temp->bt,temp->ct,tat,wt,wt); // For a non-preemptive process, WT = RT
            total_wt+=wt; // Calculating total waiting time
            total_tat+=tat; // Caluclating total turnaround time
            temp=temp->next;
            dequeue();
        }
    }
    printf("Average waiting time: %.2f\n", total_wt/n); // Dividing the total waiting time by the total number of processes
    printf("Average turnaround time: %.2f\n", total_tat/n); // Dividing the total turnaround time by the total number of processes
}
