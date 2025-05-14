#include <stdio.h>

#define MAX 10

void firstFit(int blockSize[], int m, int fileSize[], int n) {
    int allocation[MAX];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= fileSize[i]) {
                allocation[i] = j;
                blockSize[j] -= fileSize[i];
                break;
            }
        }
    }

    printf("\nMemory Management Scheme -> First Fit\n");
    printf("File_no:\tFile_size:\tBlock_no:\tBlock_size:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, fileSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, fileSize[i]);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int fileSize[], int n) {
    int allocation[MAX];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= fileSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= fileSize[i];
        }
    }

    printf("\nMemory Management Scheme -> Best Fit\n");
    printf("File_no:\tFile_size:\tBlock_no:\tBlock_size:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, fileSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, fileSize[i]);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int fileSize[], int n) {
    int allocation[MAX];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= fileSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= fileSize[i];
        }
    }

    printf("\nMemory Management Scheme -> Worst Fit\n");
    printf("File_no:\tFile_size:\tBlock_no:\tBlock_size:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, fileSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, fileSize[i]);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX], fileSize[MAX];
    int m, n, choice;

    printf("Memory Management Scheme\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    printf("Enter the number of files: ");
    scanf("%d", &n);

    printf("Enter the size of the blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the size of the files:\n");
    for (int i = 0; i < n; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &fileSize[i]);
    }

    while (1) {
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        int tempBlock[MAX];
        for (int i = 0; i < m; i++) tempBlock[i] = blockSize[i];

        switch (choice) {
            case 1: firstFit(tempBlock, m, fileSize, n); break;
            case 2: bestFit(tempBlock, m, fileSize, n); break;
            case 3: worstFit(tempBlock, m, fileSize, n); break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
