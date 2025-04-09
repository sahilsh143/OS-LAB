#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 10

// Function to calculate LCM
int lcm(int a, int b) {
    int temp_a = a, temp_b = b;
    while (temp_b != 0) {
        int t = temp_b;
        temp_b = temp_a % temp_b;
        temp_a = t;
    }
    return (a * b) / temp_a;
}

// Rate-Monotonic Scheduling
void rate_monotonic(int n, int burst[], int period[]) {
    printf("\nRate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\n", i+1, burst[i], period[i]);

    float utilization = 0;
    for (int i = 0; i < n; i++)
        utilization += (float)burst[i] / period[i];

    float bound = n * (pow(2.0, 1.0/n) - 1);
    printf("\n%f <= %f =>%s\n", utilization, bound, utilization <= bound ? "true" : "false");
}

// Earliest Deadline First Scheduling
void earliest_deadline_first(int n, int burst[], int deadline[], int period[]) {
    printf("\nEarliest Deadline Scheduling:\n");
    printf("PID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\n", i+1, burst[i], deadline[i], period[i]);

    int time = 0, total_burst = 0;
    for (int i = 0; i < n; i++) total_burst += burst[i];

    printf("\nScheduling occurs for %d ms\n", total_burst);
    int remaining[MAX];
    for (int i = 0; i < n; i++) remaining[i] = burst[i];

    while (total_burst > 0) {
        int min_deadline = 99999, index = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && deadline[i] < min_deadline) {
                min_deadline = deadline[i];
                index = i;
            }
        }
        printf("%dms : Task %d is running.\n", time, index+1);
        remaining[index]--;
        total_burst--;
        time++;
    }
}

int main() {
    int choice, n, burst[MAX], period[MAX], deadline[MAX];

    printf("Choose Scheduling Algorithm:\n1. Rate-Monotonic\n2. Earliest Deadline First\n");
    scanf("%d", &choice);

    printf("Enter the number of processes:");
    scanf("%d", &n);

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) scanf("%d", &burst[i]);

    if (choice == 1) {
        printf("Enter the time periods:\n");
        for (int i = 0; i < n; i++) scanf("%d", &period[i]);

        int l = period[0];
        for (int i = 1; i < n; i++) l = lcm(l, period[i]);
        printf("LCM=%d\n", l);

        rate_monotonic(n, burst, period);
    } else if (choice == 2) {
        printf("Enter the deadlines:\n");
        for (int i = 0; i < n; i++) scanf("%d", &deadline[i]);
        printf("Enter the time periods:\n");
        for (int i = 0; i < n; i++) scanf("%d", &period[i]);

        earliest_deadline_first(n, burst, deadline, period);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
