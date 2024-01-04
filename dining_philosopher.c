// CS21B1036
// R Anjana Narayan
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define num 5 // No of philosophers
#define eat 0   // Assigning states for eating, hungry and thinking processes in which a philosopher can be in
#define hungry 1
#define think 2
#define left (pno + 4) % num    // For a circular arrangement, these are denoting the left and right indices of a philosopher
#define right (pno + 1) % num

int philo_id[num] = {0, 1, 2, 3, 4};  // Storing the philosopher's ID
int philo_state[num];   // Keep track of the state of each philosopher

sem_t lock; // Locks when one of the philosopher tries to access a fork and prevent others from accessing it
sem_t philo_eat[num];   // They control when the philosopher can start eating, that is, when 0 they can eat and when 1, they cannot

void check_eat(int pno)
{
    if(philo_state[left] != eat && philo_state[right] != eat && philo_state[pno] == hungry) // Eat only if the philosopher is hungry and his neighbours are not eating
    {
        philo_state[pno] = eat;
        sleep(2);
        printf("Philosopher %d take the forks and started eating!\n", pno);
        sem_post(&philo_eat[pno]);    // Tells his neighbour that he finished eating and fork is available
    }
}

void keep_fork(int pno) 
{
    printf("Philosopher %d put down the forks\n", pno);
    sem_wait(&lock);    // Acquiring the lock that he is keeping down the fork
    philo_state[pno] = think;
    check_eat(left);    // Neighbours in the left and right can start eating
    check_eat(right);
    sem_post(&lock);    // Releasing the lock of fork
}

void fork_take(int pno)
{
    printf("Philosopher %d is hungry\n", pno);
    sem_wait(&lock);    // Acquiring the lock that he is picking the fork
    philo_state[pno] = hungry; 
    check_eat(pno); // If neighbours are not eating, he is eating
    sem_post(&lock);
    sem_wait(&philo_eat[pno]);
    sleep(1);
}

void *philo_action(void *digit) // This is a simulation of philosopher's actions
{
    while(1)
    {
        int *phid = digit;
        sleep(1);
        fork_take(*phid);
        sleep(0);
        keep_fork(*phid);
    }
}

int main()
{
    pthread_t tid[num];
    if(sem_init(&lock, 0, 1) == -1)
        perror("Error in semaphore!\n");
    int i;
    for (i = 0; i < num; i++)
        if(sem_init(&philo_eat[i], 0, 0) == -1)
            perror("Error in semaphore!\n");
    for (i = 0; i < num; i++) 
    {
        pthread_create(&tid[i], NULL, philo_action, &philo_id[i]);  
        printf("Philosopher %d is thinking\n", i);
    }
    pthread_join(tid[0], NULL);   // Waiting for philosopher's thread to finish
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    pthread_join(tid[4], NULL);
    return 0;
}

/*
Surya
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define num 5
sem_t chopstick[num];

void think(int i)
{
    printf("Philosopher %d Finished\n", i);
    printf("Philosopher %d Thinking\n", i);
    sleep(1);
}

void eat(int i)
{   
    printf("Philosopher %d Eating\n", i);
    sleep(1);
}

void *dine(void *arg)
{
    int i = *((int *)arg);
    while (1)
    {   
        if (i % 2 == 0)
        {
            sem_wait(&chopstick[i]);
            sem_wait(&chopstick[(i + 1) % num]);
            eat(i);
            sem_post(&chopstick[i]);
            sem_post(&chopstick[((i + 1)) % num]);
            think(i);
        }
        else
        {
            sem_wait(&chopstick[(i + 1) % num]);
            sem_wait(&chopstick[i]);
            eat(i);
            sem_post(&chopstick[((i + 1)) % num]);
            sem_post(&chopstick[i]);
            think(i);
        }
    }
}

void main()
{
    pthread_t philosopher[num];
    int index[num];

    for (int i = 0; i < num; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for (int i = 0; i < num; i++)
    {
        index[i] = i;
        pthread_create(&philosopher[i], NULL, dine, &index[i]);
    }

    for (int i = 0; i < num; i++)
    {
        pthread_join(philosopher[i], NULL);
    }
}*/