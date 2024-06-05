#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turn_around_time;
    bool completed;
} Process;

void calculate_SJF(Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    int min_index;
    bool found;

    while (completed_processes < n) {
        min_index = -1;
        found = false;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                if (!found || processes[i].burst_time < processes[min_index].burst_time) {
                    min_index = i;
                    found = true;
                }
            }
        }

        if (found) {
            current_time += processes[min_index].burst_time;
            processes[min_index].waiting_time = current_time - processes[min_index].burst_time - processes[min_index].arrival_time;
            processes[min_index].turn_around_time = processes[min_index].waiting_time + processes[min_index].burst_time;
            processes[min_index].completed = true;
            completed_processes++;
        } else {
            current_time++;
        }
    }
}

void print_average_times(Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turn_around_time;
    }
    printf("Average Waiting Time: %f\n", (double)total_waiting_time / n);
    printf("Average Turnaround Time: %f\n", (double)total_turnaround_time / n);
}

int main() {
    int n;
    printf("****************\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("****************\n");
    // Get arrival times
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
    }

    printf("****************\n");
    // Get burst times
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turn_around_time = 0;
        processes[i].completed = false;
    }

    printf("****************\n");
    calculate_SJF(processes, n);
    print_average_times(processes, n);

    return 0;
}