// CS21B1036
// R Anjana Narayan

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t write_mutex, read_mutex;
int read_count = 0;
char item[50] = "Reader-writer-problem";

void *writer(void *arg)
{
    int i;
    for (i = 0; i < 5; i++) // Limiting to write only 5 times
    {
        sem_wait(&write_mutex);
        printf("Enter the word to write: ");
        scanf("%s", item);
        sem_post(&write_mutex); // After writing, lock is released so that readers can read
        usleep(50);
    }
}

void *reader(void *arg)
{
    int i, k = *((int *)arg);
    for (i = 0; i < 3; i++) // Limiting that one reader can read only 3 times
    {
        sem_wait(&read_mutex);  // New reader acquires read lock for incrementing read count
        read_count += 1;
        if (read_count == 1)    // When one of them is reading, noone can read
            sem_wait(&write_mutex);
        sem_post(&read_mutex);
        printf("Reader number %d: %s\n", k, item);
        sem_wait(&read_mutex);  // Reader has read the file and is ready to leave
        read_count -= 1;
        if (read_count == 0)    // When no one is reading, allow writing
            sem_post(&write_mutex);
        sem_post(&read_mutex);
        usleep(50);
    }
}

int main()
{
    if(sem_init(&write_mutex, 0, 1) == -1)
        perror("Write mutex");
    if(sem_init(&read_mutex, 0, 1) == -1)
        perror("Read mutex");
    pthread_t write, read[5];   // Creating a writer thread and an array of 5 reader threads
    int ind[5], i;
    pthread_create(&write, NULL, writer, NULL);
    for(i = 0; i < 5; i++)
    {
        ind[i] = i;
        pthread_create(&read[i], NULL, reader, &ind[i]);
    }
    pthread_join(write, NULL);
    for(i = 0; i < 5; i++)
        pthread_join(read[i], NULL);
}
/*
// N Rahul
// CS21B1082

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


// Define global variables

int readers_count = 0;

sem_t read;
sem_t write;

//Reader function

void* reader(void* arg)
{
    int i=0;
    while (i<=3) 
    {
        usleep(200);

        sem_wait(&read);
        readers_count++;
        if (readers_count == 1) 
        {
            sem_wait(&write);  
        }
        sem_post(&read);

        printf("Reader is reading: %d\n", shared_resource);

        sem_wait(&read);
        readers_count--;
        if (readers_count == 0) 
        {
            sem_post(&write);  
        }
        sem_post(&read);
        i++;
    }

    return NULL;
}

// Writer function


void* writer(void* arg)
{
    int j=0;
    while (j<=5) 
    {
        usleep(200);
        sem_wait(&write);
        printf("Writer is writing...");
        sem_post(&write);
        j++;
    }

    return NULL;
}

int main() 
{
    pthread_t reader_threads[5];
    pthread_t writer_thread;

    // Initializing semaphores
    
    sem_init(&read, 0, 1);
    sem_init(&write, 0, 1);
    
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    pthread_create(&writer_thread, NULL, writer, NULL);

    // Waiting for all threads to finish 
    
    for (i = 0; i < 5; i++) 
    {
        pthread_join(reader_threads[i], NULL);
    }

    pthread_join(writer_thread, NULL);

    // Destroying semaphores
    
    sem_destroy(&read);
    sem_destroy(&write);

    return 0;
}*/