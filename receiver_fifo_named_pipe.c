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
    int file, A;
    mkfifo("myfifo", 0666);
    file = open("myfifo", O_RDONLY);	// Opening FIFO pipe in read-only mode
    if(file == -1)
    {
        printf("Error in opening the file. Exiting the program!");
        exit(0);
    }
    read(file, &A, sizeof(int));    // Read integer A from the FIFO pipe
    printf("Integer entered: %d\n", A);
    int B1 = ~A;	// Finding 1s complement of integer A
    close(file);
    file = open("myfifo", O_WRONLY);	// Opening FIFO pipe in write-only mode
    if(file == -1)
    {
        printf("Error in opening the file. Exiting the program!");
        exit(0);
    }
    write(file, &B1, sizeof(int));  // Write the 1s complement of integer A into the FIFO pipe
    close(file);	// Closing the FIFO named pipe
    return 0;
}