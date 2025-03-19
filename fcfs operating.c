#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid, at, bt, ct, tat, wt;
} Process;

void sort_by_arrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfs(Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        time = p[i].ct;
    }
}

void display(Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process *p = (Process *)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
    }
    sort_by_arrival(p, n);
    fcfs(p, n);
    printf("\n--- FCFS Scheduling ---\n");
    display(p, n);
    free(p);
    return 0;
}
OUTPUT-

Enter number of processes: 3
Enter Process ID, Arrival Time, and Burst Time for P1: 1
1
4
Enter Process ID, Arrival Time, and Burst Time for P2: 2
3
5
Enter Process ID, Arrival Time, and Burst Time for P3: 3
4
5

--- FCFS Scheduling ---

PID     AT      BT      CT      TAT     WT
1       1       4       5       4       0
2       3       5       10      7       2
3       4       5       15      11      6

Process returned 0 (0x0)   execution time : 16.095 s
Press any key to continue.
