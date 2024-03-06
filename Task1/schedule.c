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
    // Add more processes here
};

void schedule_processes_FIFO(struct Process processes[], int num_processes) {
    int current_time = 0; // Initialize current time
    printf("Process Execution Order:\n");

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



int main() {
    int num_processes = sizeof(processes) / sizeof(struct Process);
    schedule_processes_FIFO (processes, num_processes);
    return 0;
}
