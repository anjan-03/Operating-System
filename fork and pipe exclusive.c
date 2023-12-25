// CS21B1036
// R Anjana Narayan
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>

#define max_len 100

int main() 
{
    int pipe_pc[2], pipe_cg[2]; // Pipe from parent to child and child to grandchild
    char msg_pc[max_len], msg_cg[max_len];  // Message from parent to child and child to grandchild
    if(pipe(pipe_pc)==-1)
    {
        printf("Error in creating pipe. Exiting the program!");
        exit(0);
    }
    if(pipe(pipe_cg)==-1)
    {
        printf("Error in creating pipe. Exiting the program!");
        exit(0);
    }
    int pid=fork(); // Creating child process
    if(pid==-1)
    {
        printf("Fork failed. Exiting the program!");
        exit(0);
    }
    else if(pid==0) // Child process
    {
        close(pipe_pc[1]);  // Close write end of pipe_pc
        read(pipe_pc[0], msg_pc, max_len);
        close(pipe_pc[0]);  // Closing read end of pipe_pc also so that pipe_pc is not available in Child-Grandchild process
        int pid2=fork();
        if(pid2==-1)
        {
            printf("Fork failed. Exiting the program!");
            exit(0);
        }
        else if(pid2==0) // Grandchild process
        {
            close(pipe_cg[1]); // Close read end of pipe_cg
            read(pipe_cg[0], msg_cg, max_len);
            printf("In grandchild process, PID: %d\tParent PID: %d\n", getpid(), getppid());
            printf("Difference in the length of messages: %d\n", abs(strlen(msg_pc)-strlen(msg_cg)));   // Giving the absolute difference in the length
            close(pipe_cg[0]);
        }
        else    // Child process
        {
            close(pipe_cg[0]);  // Close read end of pipe_cg
            printf("Enter the message from child to grandchild: ");
            fgets(msg_cg, max_len, stdin);
            msg_cg[strcspn(msg_cg, "\n")]='\0'; // Remove newline character from the message
            write(pipe_cg[1], msg_cg, max_len);
            wait(NULL); // Wait for grandchild to finish
            printf("In child process, PID: %d\tParent PID: %d\n", getpid(), getppid());
            close(pipe_cg[1]);  // Close write end of pipe_cg
        }
    }
    else    // Parent process
    {
        close(pipe_cg[0]);  // pipe_cg not availble in Parent-Child process
        close(pipe_cg[1]);
        close(pipe_pc[0]);  // Close read end of pipe_pc
        printf("Enter the message from parent to child: ");
        fgets(msg_pc, max_len, stdin);
        msg_pc[strcspn(msg_pc, "\n")]='\0'; // Remove newline character from the message
        write(pipe_pc[1], msg_pc, max_len);
        wait(NULL); // Wait for child to finish
        printf("In parent process, PID: %d\n", getpid());
        close(pipe_pc[1]);  // // Close write end of pipe_pc
    }
    return 0;
}