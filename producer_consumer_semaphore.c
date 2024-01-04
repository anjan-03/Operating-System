// CS21B1036
// R Anjana Narayan

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int buffer[10]; // Buffer of capacity 10
int next = 0, present  = 0; // next is the position where the next item needs to be added and present is the position from where the item need to be consumed
sem_t empty, full, bsem; 
pthread_t cons_thread, prod_thread;  

int produce_item()
{
    int item = rand() % 100;    // Generating random number from 0 to 99
    printf("Item produced: %d\n", item);
    return item;    // Returning the generated number
}

void consume_item(int item)
{
    printf("Item consumed: %d\n", item);
}

void *producer(void *arg)
{
    int item, i;
    for(i = 0; i < 20; i++)
    {
        item = produce_item();  // Producing an item
        sem_wait(&empty);   // If the buffer is full, wait
        sem_wait(&bsem);    // Initialize binary semaphore
        buffer[next] = item;   // Add item to the buffer
        next = (next + 1) % 10;
        sem_post(&bsem);    // Releasing the lock on binary semaphore
        sem_post(&full);    // Signal now that the buffer is not empty
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item, i;
    for(i = 0; i < 20; i++)
    {
        sem_wait(&full);    // If the buffer is empty, wait
        sem_wait(&bsem);    
        item = buffer[present]; // Retrieves an item from the buffer
        present = (present + 1) % 10;
        sem_post(&bsem);    
        sem_post(&empty);   // Signal that the buffer is not full
        consume_item(item); // Consuming the item
    }
    pthread_exit(NULL);
}

int main()
{
    if(sem_init(&empty, 0, 10) == -1)   // Initialize empty semaphore to size of buffer
        perror("Empty");
    if(sem_init(&full, 0, 0) == -1)     // Initialize full semaphore to 0
        perror("Full");
    if(sem_init(&bsem, 0, 1) == -1)     // Initialize binary semaphore to 1
        perror("Binary semaphore");
    pthread_create(&prod_thread, NULL, producer, NULL); // Creating threads for producer and consumer
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    sem_destroy(&empty);    // Destroying empty, full and binary semaphores
    sem_destroy(&full);
    sem_destroy(&bsem);
    return 0;
}