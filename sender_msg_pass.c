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
    int key = 31155;    // Unique key between sender and receiver
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1)
    {
        printf("Error in creating queue. Exiting the program!");
        exit(0);
    }
    struct msg_list msg;
    msg.msg_type = 1;   // Message type should be greater than 0
    printf("Enter all the 10 numbers: ");
    for (int i = 0; i < size; i++) 
        scanf("%d", &msg.num[i]);   // Asking the input number from user
    msgsnd(msgid, &msg, sizeof(msg), 0);    // Sending the message to message queue
    printf("Numbers sent successfully!\n");
    return 0;
}
/*
// CS21B1082
// N Rahul

#include<stdio.h>
#include<stdlib.h>
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
    msg.mtype = 1;

    int ct;
    printf("How many numbers do you want to send to the Receiver: ");
    scanf("%d", &ct);
    for(int i = 0; i < ct; i++)
    {
        printf("Enter a number : ");
        scanf("%d", &msg.arr[i]);
    }
    msg.size = ct;
    int sndres = msgsnd(msgid, (void *)&msg, sizeof(message) - sizeof(long int), 0);
    printf("\nMessage sent to the receiver's process\n");
}
*/