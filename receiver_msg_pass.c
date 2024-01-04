// CS21B1036
// R Anjana Narayan
#include <stdio.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define size 10

struct msg_list // Structure containing message type and data
{
    long msg_type;
    int num[size];
};

int main() 
{
    int i, odd=0;
    int key = 31155;    // Unique key between sender and receiver
    int msgid = msgget(key, 0644);
    if(msgid == -1)
    {
        printf("Error in creating queue. Exiting the program!");
        exit(0);
    }
    struct msg_list msg;
    msgrcv(msgid, &msg, sizeof(msg), 1, 0); // Receiving the msg from the msg queue
    printf("Odd numbers: ");
    for (i = 0; i < size; i++) 
        if (msg.num[i] % 2 != 0)    // Checking if the number is odd or not
        {
            odd++;
            printf("%d ", msg.num[i]);  // Display all the odd numbers
        }
    printf("\nTotal odd numbers: %d\n", odd);   // Print total number of odd
    return 0;
}
/*
// CS21B1082
// N Rahul

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct message
{
    long int mtype;
    int arr[100];
    int size;
};
typedef struct message message;

int main()
{
    int msgid = msgget(12420, 0666 | IPC_CREAT);

    message msg;
    msgrcv(msgid, (void *)&msg, sizeof(message) - sizeof(long int), 1, 0);

    int oddct = 0;
    printf("Odd numbers sent from the sender's process are : ");
    for(int i = 0; i < msg.size; i++)
    {
        if(msg.arr[i] % 2)
        {
            printf("%d ", msg.arr[i]);
            oddct++;
        }
    }
    printf("\nNumber of odd numbers from sender : %d\n", oddct);

    msgctl(msgid, IPC_RMID, 0);
}
*/