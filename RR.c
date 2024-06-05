#include <stdio.h>
#include <stdbool.h>

void roundRobin(int n, int arrival_time[], int burst_time[], int quantum) {
    int waiting_time[n], remaining_burst_time[n];
    int total_waiting_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = burst_time[i];
        waiting_time[i] = 0;
    }

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (remaining_burst_time[i] > 0) {
                done = false;

                if (remaining_burst_time[i] > quantum) {
                    current_time += quantum;
                    remaining_burst_time[i] -= quantum;
                } else {
                    current_time += remaining_burst_time[i];
                    waiting_time[i] = current_time - burst_time[i] - arrival_time[i];
                    total_waiting_time += waiting_time[i];
                    remaining_burst_time[i] = 0;
                }
            }
        }

        if (done) break;
    }

    double average_waiting_time = (double) total_waiting_time / n;

    printf("RR Average Waiting Time: %.2f\n", average_waiting_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("****************\n");

    int arrival_time[n], burst_time[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }

    printf("****************\n");

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("****************\n");

    int quantum;
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    printf("****************\n");

    roundRobin(n, arrival_time, burst_time, quantum);

    return 0;
}

