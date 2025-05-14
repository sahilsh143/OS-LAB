#include <stdio.h>
#include <limits.h>

void fifo(int pages[], int n, int frames) {
    int frame[frames], index = 0, faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            faults++;
        }
    }

    printf("FIFO Page Faults = %d\n", faults);
}



void lru(int pages[], int n, int frames) {
    int frame[frames], time[frames], faults = 0, t = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                time[j] = t++;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[lruIndex]) lruIndex = j;
            }
            frame[lruIndex] = pages[i];
            time[lruIndex] = t++;
            faults++;
        }
    }

    printf("LRU Page Faults = %d\n", faults);
}

int predict(int pages[], int frame[], int n, int index, int frames) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimal(int pages[], int n, int frames) {
    int frame[frames], count = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int empty = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
                frame[empty] = pages[i];
            else {
                int j = predict(pages, frame, n, i + 1, frames);
                frame[j] = pages[i];
            }
            count++;
        }
    }

    printf("OPTIMAL Page Faults = %d\n", count);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
