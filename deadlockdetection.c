#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], available[m], finish[n];

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d : ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d : ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;
    int safeSeq[n];

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    finish[i] = 1;
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    bool deadlock = false;
    for (int i = 0; i < n; i++)
        if (!finish[i])
            deadlock = true;

    if (!deadlock) {
        printf("System is in safe state.\n");
        printf("Safe Sequence is: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is in deadlock.\nProcesses involved: ");
        for (int i = 0; i < n; i++)
            if (!finish[i])
                printf("P%d ", i);
        printf("\n");
    }

    return 0;
}
