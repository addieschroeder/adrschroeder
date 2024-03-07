#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
};

// Example test processes
struct Process processes[] = {
    {1, 0, 10},
    {2, 2, 5},
    {3, 4, 8},
    {4, 0, 1},
    {5, 5, 9},
    // Add more processes here
};

void schedule_processes_FIFO(struct Process processes[], int num_processes) {
    int current_time = 0; // Initialize current time
    printf("\nProcess Execution Order (FIFO):\n");

    for (int i = 0; i < num_processes; ++i) {
        // Wait until the process arrives (if needed)
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // Execute the process
        printf("Executing Process %d (Burst Time: %d)\n", processes[i].pid, processes[i].burst_time);
        current_time += processes[i].burst_time;

        // Calculate turnaround time and response time
        int turnaround_time = current_time - processes[i].arrival_time;
        printf("Turnaround Time for Process %d: %d\n", processes[i].pid, turnaround_time);
        // Response time measurement need to be implemented.
    }
}

// Implement shortest job first (SJF) algorithm
void schedule_processes_SJF(struct Process processes[], int num_processes) {
     int current_time = 0; // Initialize current time to zero 

    // Sort the processes by burst time
    for (int i = 0; i < num_processes - 1; i++) {
        int min = i;
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[j].burst_time < processes[min].burst_time) {
                min = j;
            }
        }
        // Swap the minimum element with the first element
        struct Process temp = processes[i];
        processes[i] = processes[min];
        processes[min] = temp;
    }

    printf("\nProcess Execution Order (SJF):\n");
    for (int i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        printf("Executing Process %d (Burst Time: %d)\n", processes[i].pid, processes[i].burst_time);
        current_time += processes[i].burst_time;
        int turnaround_time = current_time - processes[i].arrival_time;
        printf("Turnaround Time for Process %d: %d\n", processes[i].pid, turnaround_time);
    }
}

// Implement shortest remaining job first (SRJF) algorithm
void schedule_processes_SRJF(struct Process processes[], int num_processes) {
    int current_time = 0, completed = 0;
    int min_remaining_time, shortest;

    // Initialize remaining times for all processes (equal to burst time)
    int remaining_time[num_processes];
    for (int i = 0; i < num_processes; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    printf("\nProcess Execution Order (SRJF):\n");
    while (completed < num_processes) {
        min_remaining_time = __INT_MAX__;
        shortest = -1;
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && remaining_time[i] > 0 && remaining_time[i] < min_remaining_time) {
                min_remaining_time = remaining_time[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        remaining_time[shortest]--;
        if (remaining_time[shortest] == 0) {
            completed++;
            int turnaround_time = current_time + 1 - processes[shortest].arrival_time;
            printf("Turnaround Time for Process %d: %d\n", processes[shortest].pid, turnaround_time);
        }
        current_time++;
    }
}


int main() {
    int num_processes = sizeof(processes) / sizeof(struct Process);
    schedule_processes_FIFO (processes, num_processes);
    schedule_processes_SJF(processes, num_processes);
    schedule_processes_SRJF(processes, num_processes);
    return 0;
}
