#include <stdio.h>

#define MAX 10


typedef struct {
    int pid;
    int arrival;
    int burst;
} Process;


void sortByArrival(Process queue[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (queue[i].arrival > queue[j].arrival) {
                Process temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }
}


void executeFCFS(Process queue[], int n) {
    int time = 0;
    printf("\nExecuting FCFS Queue:\n");
    for (int i = 0; i < n; i++) {
        if (time < queue[i].arrival)
            time = queue[i].arrival;
        printf("Process %d runs from %d to %d\n", queue[i].pid, time, time + queue[i].burst);
        time += queue[i].burst;
    }
}


void executeRoundRobin(Process queue[], int n, int quantum) {
    int remaining[MAX], time = 0, done = 0;
    for (int i = 0; i < n; i++)
        remaining[i] = queue[i].burst;

    printf("\nExecuting Round Robin Queue (Quantum = %d):\n", quantum);
    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                int runTime = (remaining[i] < quantum) ? remaining[i] : quantum;
                printf("Process %d runs from %d to %d\n", queue[i].pid, time, time + runTime);
                time += runTime;
                remaining[i] -= runTime;
                if (remaining[i] == 0)
                    done++;
            }
        }
    }
}

int main() {
    int sys_n, int_n, batch_n, quantum;

    printf("Enter number of System processes: ");
    scanf("%d", &sys_n);
    Process systemQueue[MAX];
    for (int i = 0; i < sys_n; i++) {
        printf("Enter PID, Arrival Time & Burst Time for System Process %d: ", i + 1);
        scanf("%d %d %d", &systemQueue[i].pid, &systemQueue[i].arrival, &systemQueue[i].burst);
    }

    printf("Enter number of Interactive processes: ");
    scanf("%d", &int_n);
    Process interactiveQueue[MAX];
    for (int i = 0; i < int_n; i++) {
        printf("Enter PID, Arrival Time & Burst Time for Interactive Process %d: ", i + 1);
        scanf("%d %d %d", &interactiveQueue[i].pid, &interactiveQueue[i].arrival, &interactiveQueue[i].burst);
    }

    printf("Enter time quantum for Round Robin queue: ");
    scanf("%d", &quantum);

    printf("Enter number of Batch processes: ");
    scanf("%d", &batch_n);
    Process batchQueue[MAX];
    for (int i = 0; i < batch_n; i++) {
        printf("Enter PID, Arrival Time & Burst Time for Batch Process %d: ", i + 1);
        scanf("%d %d %d", &batchQueue[i].pid, &batchQueue[i].arrival, &batchQueue[i].burst);
    }


    sortByArrival(systemQueue, sys_n);
    sortByArrival(batchQueue, batch_n);


    executeFCFS(systemQueue, sys_n);
    executeRoundRobin(interactiveQueue, int_n, quantum);
    executeFCFS(batchQueue, batch_n);

    return 0;
}

