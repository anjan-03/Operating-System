// CS21B1036
// R Anjana Narayan
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main() 
{
    int file, A, B1;
    printf("Enter a number to find 1s complement: ");
    scanf("%d", &A);	// Getting input from user
    mkfifo("myfifo", 0666);	// Create FIFO named pipe
    file = open("myfifo", O_WRONLY);	// Opening FIFO pipe in write-only mode
    if(file == -1)
    {
        printf("Error in opening the file. Exiting the program!");
        exit(0);
    }
    write(file, &A, sizeof(int));	// Write the integer n into the FIFO pipe
    close(file);	// Close the FIFO named pipe
    file = open("myfifo", O_RDONLY);	// Opening FIFO pipe in read-only mode
    if(file == -1)
    {
        printf("Error in opening the file. Exiting the program!");
        exit(0);
    }
    read(file, &B1, sizeof(int));
    printf("The 1s complement of %d is %d\n", A, B1);
    close(file);
    return 0;
}
