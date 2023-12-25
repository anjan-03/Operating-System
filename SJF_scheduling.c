//CS21B1036
// R Anjana Narayan
#include<stdio.h>
#include<stdlib.h>

struct data // Store information about each process
{
    int p_id, a_t, b_t, c_t;
};

struct heap // Defines a node for the min-heap used for scheduling processes. 
{
    int prior, var;
    struct data info;
    struct heap *top, *left, *right;
};

struct heap *root = NULL;
int size = 0; // No of nodes in min heap

int parent(int n)
{
    return n/2;
}

int int_to_bin(int n) // Convert integer into its binary form
{
    return (n == 0 || n == 1 ? n : ((n % 2) + 10 * int_to_bin(n / 2)));
}

struct heap * traverse(int var)
{
    int i;
    char sent[12];
    sprintf(sent, "%d", int_to_bin(var));
    struct heap *ptr = root;
    for(i = 1; sent[i] != '\0'; i++)
    {
        if(sent[i] == '1')
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }
    return ptr;
}

void heapify_up(struct heap *ptr) // Maintains the min-heap property by recursively swapping nodes upwards
{
    if(ptr == root)
        return;
    if(ptr->prior < ptr->top->prior )
    {
        struct data ptr_data = ptr->info;
        int ptr_prior = ptr->prior;
        ptr->info = ptr->top->info;
        ptr->prior = ptr->top->prior;
        ptr->top->info = ptr_data;
        ptr->top->prior = ptr_prior;
        heapify_up(ptr->top);
    }
}

void heapify_down(struct heap *ptr) // Maintains the min-heap property by recursively swapping nodes downwards.
{
    struct heap *l = ptr->left; // Left node
    struct heap *r = ptr->right; // Right node
    struct heap *mini = NULL; // Minimum node
    if(l != NULL && l->prior < ptr->prior)
        mini = l;
    else
        mini = ptr;
    if(r != NULL && r->prior < mini->prior)
        mini = r;
    if(mini != ptr)
    {
        struct data ptr_data = ptr->info;
        int ptr_prior = ptr->prior;
        ptr->info = mini->info;
        ptr->prior = mini->prior;
        mini->info = ptr_data;
        mini->prior = ptr_prior;
        heapify_down(mini);
    }
}

void insert(struct data info, int prior) // Inserts a process into the min-heap based on its burst time priority
{
    struct heap *ptr = (struct heap *)malloc(sizeof(struct heap));
    if(ptr==NULL)
    {
        printf("Memory not allocated properly!");
        exit(0);
    }
    ptr->info = info;
    ptr->prior = prior;
    size++;
    ptr->var = size;
    ptr->top = NULL;
    ptr->left = NULL;
    ptr->right = NULL;
    if(root == NULL)
        root = ptr;
    else
    {
        struct heap *temp = traverse(parent(ptr->var));
        if(temp->left == NULL)
        {
            temp->left = ptr;
            ptr->top = temp;
        }
        else
        {
            temp->right = ptr;
            ptr->top = temp;
        }
        heapify_up(ptr);
    }
}

struct heap extract() // Extracts the process with the smallest burst time from the min-heap, heapifies, and returns the extracted process.
{
    if(root == NULL || size == 0)
    {
        printf("Underflow!");
        return *root;
    }
    if(root->left == NULL && root->right == NULL)
    {
        struct heap ptr1 = *root;
        root = NULL;
        size--;
        return ptr1;
    }
    struct heap ptr1 = *root;
    struct heap *ptr = traverse(size);
    root->info = ptr->info;
    root->prior = ptr->prior;
    if(ptr->top->left == ptr)
        ptr->top->left = NULL;
    else
        ptr->top->right = NULL;
    free(ptr);
    size--;
    heapify_down(root);
    return ptr1;
}

struct heap2 // Defines a node for a linked list queue used for process enqueueing
{
    int p_id, a_t, b_t, c_t;
    struct heap2 *next;
};

struct heap2 *front = NULL;
struct heap2 *rear = NULL;

void enqueue(int p_id, int a_t, int b_t, int c_t)
{
    struct heap2 *ptr = (struct heap2 *)malloc(sizeof(struct heap2));
    if(ptr==NULL)
    {
        printf("Memory not allocated properly!");
        exit(0);
    }
    ptr->p_id = p_id;
    ptr->a_t = a_t;
    ptr->b_t = b_t;
    ptr->c_t = c_t;
    ptr->next = NULL;
    if((front == NULL) && (rear == NULL))
    {
        front = ptr;
        rear = ptr;
        front->next = NULL;
    }
    else
    {
        ptr->next = NULL;
        rear->next = ptr;
        rear = ptr;
    }
}

struct heap2 dequeue()
{
    if(front == NULL)
    {
        printf("Underflow!\n");
        return *front;
    }
    else if(front == rear)
    {
        struct heap2 ptr1 = *front;
        front = NULL;
        rear = NULL;
        return ptr1;
    }
    else
    {
        struct heap2 ptr1 = *front;
        struct heap2 *ptr = front;
        front = front->next;
        free(ptr);
        return ptr1;
    }
}

int main()
{
    int n, i, temp = 0;
    struct heap2 *ptr;
    float total_wt = 0, total_tat = 0;
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    printf("\nEnter the processes on the increasing order of arriving time!\n\n");
    for(i = 0; i < n; i++)
    {
        int p_id, a_t, b_t;
        printf("Enter the process ID: ");
        scanf("%d", &p_id);
        printf("Enter the arriving time: ");
        scanf("%d", &a_t);
        printf("Enter the burst time: ");
        scanf("%d", &b_t);
        struct data data1;
        data1.p_id = p_id;
        data1.a_t = a_t;
        data1.b_t = b_t;
        if(i==0)
            temp = a_t;
        while(a_t > temp && size != 0)
        {
            struct heap ptr2 = extract();
            temp += ptr2.info.b_t;
            ptr2.info.c_t = temp;
            enqueue(ptr2.info.p_id, ptr2.info.a_t, ptr2.info.b_t, ptr2.info.c_t);
        }
        insert(data1, b_t);
    }
    while(size != 0)
    {
        struct heap ptr2 = extract();
        temp += ptr2.info.b_t;
        ptr2.info.c_t = temp;
        enqueue(ptr2.info.p_id, ptr2.info.a_t, ptr2.info.b_t, ptr2.info.c_t);
    }
    printf("PID\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    if((front == NULL) && (rear == NULL))
        printf("No processes scheduled!\n");
    else
    {
        while(front != NULL)
        {
            ptr = front;
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ptr->p_id, ptr->a_t, ptr->b_t, ptr->c_t, ptr->c_t - ptr->a_t, ptr->c_t - ptr->a_t - ptr->b_t, ptr->c_t - ptr->a_t - ptr->b_t);
            total_wt += ptr->c_t - ptr->a_t - ptr->b_t;
            total_tat += ptr->c_t - ptr->a_t;
            dequeue(); 
        }
    }
    printf("Average weighting time: %.2f\n", total_wt/n);
    printf("Average turnaround time: %.2f\n", total_tat/n);
}