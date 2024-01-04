// CS21B1036
// R Anjana Narayan

#include<stdio.h>

int main()
{
    int i, j, n, r, next_pro, count = 0; 
    int max[10][10], need[10][10], alloc[10][10], avail[10], completed[10], safe_seq[10];
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    printf("Enter the total number of resources: ");
    scanf("%d", &r);
    printf("Enter the max matrix for each process :-\n");
    for(i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        for(j = 0; j < r; j++)
            scanf("%d", &max[i][j]); // Ask maximum resource need for each process from user
    }
    printf("\nEnter the allocation for each process :-\n5");
    for(i = 0; i < n; i++)
    {
        printf("Process %d: ",i + 1);
        for(j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]); // Ask resource allocation for each process from user
    }
    printf("\nEnter the available resources after every process is allocated initially: ");
    for(i = 0; i < r; i++)
        scanf("%d", &avail[i]); // Ask available resources from user
    for(i = 0; i < n; i++)
        completed[i] = 0; // Track the completion status of processes
    for(i = 0; i < n; i++)  
        for(j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j]; // Calculate the resource needed for each process
    do
    {
        printf("\nMax matrix\tAllocation matrix\n");
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < r; j++)
                printf("%d  ", max[i][j]); // Display the Max matrix.
            printf("\t\t");
            for(j = 0; j < r; j++)
                printf("%d  ", alloc[i][j]); // Display the Allocation matrix.
            printf("\n");
        }
        next_pro = -1;  // Next process which is going to the safe sequence
        for(i = 0; i < n; i++)
        {
            if(completed[i] == 0) // If the process is not yet completed.
            {
                next_pro = i;   // If process is not completed, checking if it can be the next safe sequence process 
                for(j = 0; j < r; j++)
                    if(avail[j] < need[i][j]) // Check if available resources are less than needed.
                    {
                        next_pro = -1;
                        break;
                    }
            }
            if(next_pro != -1)  // Next process for the safe sequence is found, so continue with it
                break;
        }
        if(next_pro != -1)
        {
            printf("\nProcess %d is completed and is added to safe sequence!", next_pro + 1);
            safe_seq[count] = next_pro + 1;
            count += 1;
            for(j = 0; j < r; j++)
            {
                avail[j] += alloc[next_pro][j]; // Release allocated resources
                alloc[next_pro][j], max[next_pro][j] = 0, 0; // Marking allocated resources and Max resources as 0.
                completed[next_pro] = 1; // Marking the process as completed
            }
        }
    } while(count != n && next_pro != -1); // Continue until all processes are completed or no safe process can run.
    if(count == n)
    {
        printf("\nThis system is in a safe state!\n");
        printf("Safe Sequence: ");
        for( i = 0; i < n; i++)
            printf("%d  ", safe_seq[i]); // Displaying the safe sequence.
        printf("\n");
    }
    else
        printf("\nThis system reaches an unsafe state!");
    return 0;
}
/*
Jawa
#include <stdio.h>
#include <stdlib.h>
// include<conio.h>

int max[100][100];
int alloc[100][100];
int need[100][100];
int avail[100];
int n, r;

void input();

void show();

void cal();

void request();

int main()
{
    int i, j;
    printf("********** Banker's Algo ************\n");
    input();
    cal();
    show();
    request();
    // getch();
    return 0;
}

void input()
{
    int i, j;
    printf("Enter the no of Processes\t");
    scanf("%d", &n);
    printf("Enter the no of resources instances\t");
    scanf("%d", &r);
    printf("Enter the Max Matrix\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the Allocation Matrix\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter the available Resources\n");
    for (j = 0; j < r; j++)
    {
        scanf("%d", &avail[j]);
    }
}

void show()
{
    int i, j;
    printf("P\t\t Allot\t\t\t Need\t\t\t Max\t\t\t Avail");
    for (i = 0; i < n; i++)
    {
        printf("\nP%d\t\t ", i + 1);
        for (j = 0; j < r; j++)
        {
            printf("%d ", alloc[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\t\t");
        if (i == 0)
        {
            for (j = 0; j < r; j++)
                printf("%d ", avail[j]);
        }
    }
}

void cal()
{
    int finish[100], flag = 1, k, c1 = 0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    // find need matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("\n");
    while (flag)
    {
        flag = 0;
        for (i = 0; i < n; i++)
        {
            int c = 0;
            for (j = 0; j < r; j++)
            {
                if ((finish[i] == 0) && (need[i][j] <= avail[j]))
                {
                    c++;
                    if (c == r)
                    {
                        for (k = 0; k < r; k++)
                        {
                            avail[k] += alloc[i][k];
                            finish[i] = 1;
                            flag = 1;
                        }
                        printf("P%d->", i);
                        if (finish[i] == 1)
                        {
                            i = n;
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (finish[i] == 1)
        {
            c1++;
        }
        else
        {
            printf("P%d->", i);
        }
    }
    if (c1 == n)
    {
        printf("\n SAFE\n");
    }
    else
    {
        // printf("\n Process are in dead lock\n");
        printf("\n UNSAFE\n");
    }
}

void request()
{
    int c, pid, request[100][100], i;
    printf("\n Do you want make an additional request for any of the process ? (1=Yes|0=No)");
    scanf("%d", &c);
    if (c == 1)
    {
        printf("\n Enter process number : ");
        scanf("%d", &pid);
        printf("\n Enter additional request : \n");
        for (i = 0; i < r; i++)
        {
            printf(" Request for resource %d : ", i + 1);
            scanf("%d", &request[0][i]);
        }
        for (i = 0; i < r; i++)
        {
            if (request[0][i] > need[pid][i])
            {
                printf("\n ******Error encountered******\n");
                exit(0);
            }
        }
        for (i = 0; i < r; i++)
        {
            avail[i] -= request[0][i];
            alloc[pid][i] += request[0][i];
            need[pid][i] -= request[0][i];
        }
        cal();
        // getch();
    }
    else
    {
        exit(0);
    }
}*/