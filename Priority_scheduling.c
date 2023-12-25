#include<stdio.h>
#include<stdlib.h>

struct proc{
  int p_id;
  int at;
  int bt;
  int pr;
  int ft;
  int rt;
  int wt;
  int tat;
};

int queue_size = 0;
int front = -1; 
int rear = -1;
struct proc * queue[1000];

struct proc * create_proc(int p_id, int at, int pr, int bt){
    struct proc * process = (struct proc *)malloc(sizeof(struct proc));
    process->p_id = p_id;
    process->at = at;
    process->pr = pr;
    process->bt = bt;
    process->rt = bt;
    process->ft = 0;
    return process;
}

void display_processes(struct proc * processes[], int n){
    printf("P_Id\tAT\tPR\tBT\tFT\n");
    for (int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i]->p_id, processes[i]->at, processes[i]->pr,processes[i]->bt,processes[i]->ft);
    }
}

void display(struct proc * processes[], int n){
    printf("P_Id\tAT\tPR\tBT\tFT\tWT\tTAT\n");
    for (int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i]->p_id, processes[i]->at, processes[i]->pr,processes[i]->bt,processes[i]->ft, processes[i]->wt, processes[i]->tat);
    }
}

void display_queue(){
    if (front == rear){
        printf("P_Id\tAT\tPR\tBT\tFT\n");
        for (int i = front; i <= rear; i++){
            printf("%d\t%d\t%d\t%d\t%d\n", queue[i]->p_id, queue[i]->at, queue[i]->pr,queue[i]->bt,queue[i]->ft);
        }
    }
    else{
        printf("P_Id\tAT\tPR\tBT\tFT\n");
        for (int i = front; i <= rear; i++){
            printf("%d\t%d\t%d\t%d\t%d\n", queue[i]->p_id, queue[i]->at, queue[i]->pr,queue[i]->bt,queue[i]->ft);
        }
    }
}

void enqueue(struct proc * process){
    if(rear == 999){
        printf("Queue overflow");
    }
    else{
        if(front == -1)
            front = 0;
        
        // printf("UPdated rear, p_id = %d\n", process->p_id);
        queue[rear+1] = (struct proc *)malloc(sizeof(struct proc));
        queue[rear+1]->p_id = process->p_id;
        queue[rear+1]->at = process->at;
        queue[rear+1]->pr = process->pr;
        queue[rear+1]->bt = process->bt;
        queue[rear+1]->rt = process->rt;
        queue[rear+1]->ft = process->ft;
        rear = rear + 1;
        queue_size++;
    }
}

struct proc * dequeue(){
    int i;
    if (front == -1 || front > rear){
        printf("Underflow\n");
    }
    else{
        
        front = front + 1;
    }
    return queue[front - 1];
}

// void sort_processes(){
//     if (front > rear){
//         return;
//     }

//     for (int i = front; i < rear - 1; i++){
//         for (int j = front; j < rear - i - 1; j++){

//             if((queue[j]->pr > queue[j+1]->pr) || (queue[j]->pr == queue[j+1]->pr && queue[j]->at > queue[j+1]->at)){
//                 struct proc * temp = queue[j];
                

//                 printf("%d\t%d\t%d\t%d\t%d\n", queue[i]->p_id, queue[i]->at, queue[i]->pr,queue[i]->bt,queue[i]->ft);
//                 printf("Identified: given p_id %d, pr %d and j+1 p_id %d pr %d\n", queue[j]->p_id, queue[j]->pr, queue[j+1]->p_id, queue[j+1]->pr);
//                 queue[j] = queue[j+1];
//                 // queue[j]->p_id = queue[j+1]->p_id;
//                 // queue[j]->at = queue[j+1]->at;
//                 // queue[j]->bt = queue[j+1]->bt;
//                 // queue[j]->rt = queue[j+1]->rt;
//                 // queue[j]->pr = queue[j+1]->pr;
                
//                 queue[j+1] = temp;

//                 printf("After swap: given p_id[j] %d, pr[j] %d and [j+1] p_id %d pr %d\n", queue[j]->p_id, queue[j]->pr, queue[j+1]->p_id, queue[j+1]->pr);
//                 printf("%d\t%d\t%d\t%d\t%d\n", queue[i]->p_id, queue[i]->at, queue[i]->pr,queue[i]->bt,queue[i]->ft);
//             }
//         }
//     }
//     printf("Printing the queue after sort process within the function: \n");
//     display_queue();
// }

void sort_processes(){
    for (int i = front + 1; i <= rear; i++){
        struct proc * temp = queue[i];
        int j = i - 1;
        while (j >= front && (queue[j]->pr > temp->pr || (queue[j]->pr == temp->pr && queue[j]->at > temp->at))){
            queue[j + 1] = queue[j];
            j = j - 1;
        }
        queue[j + 1] = temp;
    }
}




void schedule_proc(struct proc * processes[], int n){
    int cur_time = 0;
    // comp_proc stores the number of completed processes
    int comp_proc = 0;
    int visited[100];
    int visited_c = 0;
    while (comp_proc < n || queue_size > 0) {
        // Continue until all the processes are completed
        for (int i = 0; i < n; i++){
            // process arrives before current time and it has some BT for CPU
            
            // Check if the process is already in the queue
            int flag = 0;
            for (int j =0; j < visited_c; j++){
                if (processes[i]->p_id == visited[j]){
                    flag = 1;
                } 
            }
            printf("process p_id:%d, at: %d, cur_time: %d, ft = %d\n", processes[i]->p_id, processes[i]->at, cur_time, processes[i]->ft);
            if (processes[i] -> at <= cur_time && processes[i]->rt > 0 && flag == 0){
                // Add such processes to the queue
                if (processes[i]->at == 5){
                    printf("OKAY OKAY\n\n");
                }
                visited[visited_c] = processes[i]->p_id;
                visited_c++;
                enqueue(processes[i]);
            }
        }
        
        // Next we need to sort the processes based on their pr, then at, then p_id
        sort_processes();
        //display_processes(queue, queue_size);
        printf("Queue outside the sort: \n");
        printf("current time: %d\n", cur_time);
        display_queue();
        
        printf("\nfront = %d, rear = %d\n", front, rear);
        if (queue_size != 0){
            printf("front = %d\n", front);
            if(queue[front]->rt == 1){
                queue[front]->rt = 0;
                struct proc * cur_proc = dequeue();
                //front = front + 1;
                queue_size--;
                printf("\nDetail of latest process%d, %d, %d, %d\n", cur_proc->p_id, cur_proc->at, cur_proc->bt, cur_proc->pr);
                cur_time++;
                printf("\n Time when this process gets over: %d\n", cur_time);
                comp_proc++;
                // printf("computed processes: %d\n", comp_proc);
                processes[cur_proc->p_id - 1]->ft = cur_time;
            }
            else{
                queue[front]->rt -= 1;
                cur_time++;
            }
        }
        
    }
}

int main(){
    int n = 6, i;
    struct proc* processes[6];
    int p_id[] = {1,2,3,4,5,6};
    int arrival_time[] = {0,1,2,2,3,5};
    int priority[] = {3,2,1,2,4,1};
    int burst_time[] = {4,4,2,2,2,1};
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        printf("Enter process id of process %d: ", i+1);
        scanf("%d", &p_id[i]);
        printf("Enter arrival time of process %d: ", i+1);
        scanf("%d", &arrival_time[i]);
        printf("Enter priority of process %d: ", i+1);
        scanf("%d", &priority[i]);
        printf("Enter burst time of process %d: ", i+1);
        scanf("%d", &burst_time[i]);
    }
    // Create an array of structs
    // int p_id[] = {1,2,3,4,5,6, 7};
    // int arrival_time[] = {0,1,3,4,5,6,10};
    // int priority[] = {3,4,4,5,2,6,1};
    // int burst_time[] = {8,2,4,1,6,5,1};
    
    
    for (i = 0; i < n; i++){
        processes[i] = create_proc(p_id[i], arrival_time[i], priority[i], burst_time[i]);
    }
    
    display_processes(processes, n);
    
    schedule_proc(processes, n);
    
    display_processes(processes, n);
    float awt = 0;
    float atat = 0;
    for (int i = 0; i < n; i++){
        processes[i]->tat = processes[i]->ft - processes[i]->at;
        processes[i]->wt = processes[i]->tat - processes[i]->bt;
        awt += processes[i]->wt;
        atat += processes[i]->tat;
    }

    awt = awt / n;
    atat = atat / n;

    display(processes, n);

    printf("The average waiting time is: %.2f\n", awt);
    printf("The average Turn Around Time is: %.2f", atat);
    return 0;
}