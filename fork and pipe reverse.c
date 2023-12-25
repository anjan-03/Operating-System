// CS21B1036
// R Anjana Narayan
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define max_len 100

int main() 
{
    int send_pipe[2], rec_pipe[2];  // Pipe for sending the string to the child and receiving the reversed string from the child
    char inp_str[max_len], rev_str[max_len];
    if(pipe(send_pipe)==-1) // Creating send_pipe
    {
        printf("Error in creating the pipe. Exiting the program!");
        exit(0);
    }
    if(pipe(rec_pipe)==-1)  // Creating rec_pipe
    {
        printf("Error in creating the pipe. Exiting the program!");
        exit(0);
    }
    printf("Enter the string to be reversed: ");
    fgets(inp_str, max_len, stdin);
    inp_str[strcspn(inp_str, "\n")]='\0';   // Remove newline character from the input string
    int pid=fork(); // Creating child process
    if(pid==-1)
    {
        printf("Fork failed. Exiting the program!");
        exit(0);
    }
    if(pid==0)  // Child process
    {
        close(send_pipe[1]); // Close write end of send_pipe
        close(rec_pipe[0]); // Close read end of rec_pipe
        read(send_pipe[0], inp_str, max_len);   // Read the string from send_pipe
        int i, len=strlen(inp_str);
        for(i=0;i<len/2;i++)    // Reverse the string
        {
            char ch=inp_str[i];
            inp_str[i]=inp_str[len-i-1];
            inp_str[len-i-1]=ch;
        }
        write(rec_pipe[1], inp_str, max_len); // Write the reversed string to rec_pipe
        close(send_pipe[0]);    // Close read end of send_pipe
        close(rec_pipe[1]);     // Close write end of rec_pipe
        exit(0);
    }
    else    // Parent process 
    {
        close(send_pipe[0]); // Close read end of send_pipe
        close(rec_pipe[1]); // Close write end of rec_pipe
        write(send_pipe[1], inp_str, max_len);    // Write the input string to send_pipe
        read(rec_pipe[0], rev_str, max_len);    // Read the reversed string from rec_pipe
        printf("Reversed string is: %s\n", rev_str);
        close(send_pipe[1]);    // Close write end of send_pipe
        close(rec_pipe[0]);     // Close read end of rec_pipe
    }
    return 0;
}