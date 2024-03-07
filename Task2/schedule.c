#include <stdio.h>
#include <stdbool.h>

// Print turnaround time, response time
// Report average turnaround time and response time 

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int response_time;
    int avg_turnaround_time;
    int avg_response_time;
    bool started;
};

// Example test processes
struct Process processes[] = {
    {1, 0, 8},
    {2, 1, 5},
    {3, 2, 10},
    {4, 3, 3},
    {5, 4, 6},
    {6, 5, 7},
    {7, 6, 4},
    {8, 7, 9},
    {9, 8, 2},
    {10, 9, 5},
    {11, 10, 6},
    {12, 11, 8},
    {13, 12, 4},
    {14, 13, 7},
    {15, 14, 3},
    {16, 15, 6},
    {17, 16, 5},
    {18, 17, 4},
    {19, 18, 7},
    {20, 19, 9}
};

void schedule_processes_FIFO(struct Process processes[], int num_processes) {
    int current_time = 0; // Initialize current time
    double total_turnaround_time = 0.0;
    double total_response_time = 0.0;


    printf("\nProcess Execution (FIFO):\n");

    for (int i = 0; i < num_processes; ++i) {
        // Wait until the process arrives (if needed)
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // Calculate response time
        processes[i].response_time = current_time - processes[i].arrival_time;

        // Update the current time
        current_time += processes[i].burst_time;  

        // Calculate turnaround time
        processes[i].turnaround_time = current_time - processes[i].arrival_time;

        // Update total response and turnaround times 
        total_response_time += processes[i].response_time;
        total_turnaround_time += processes[i].turnaround_time;

        // Print results 
        printf("Response Time for Process %d: %d\n", processes[i].pid, processes[i].response_time);
        printf("Turnaround Time for Process %d: %d\n\n", processes[i].pid, processes[i].turnaround_time);
    }
    
    // Print average turnaround and response times
    printf("Average Response Time: %.2f\n", total_response_time / num_processes);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / num_processes);
}

// Implement shortest job first (SJF) algorithm
void schedule_processes_SJF(struct Process processes[], int num_processes) {
    int current_time = 0; // Initialize current time to zero 
    double total_turnaround_time = 0.0;
    double total_response_time = 0.0;

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

    printf("\nProcess Execution (SJF):\n");
    for (int i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        // Calculate response time 
        processes[i].response_time = current_time - processes[i].arrival_time;

        // Execute process
        current_time += processes[i].burst_time;

        // Calculate turnaround time
        processes[i].turnaround_time = current_time - processes[i].arrival_time;

        // Update total response and turnaround times 
        total_response_time += processes[i].response_time;
        total_turnaround_time += processes[i].turnaround_time;

        // Print results 
        printf("Response Time for Process %d: %d\n", processes[i].pid, processes[i].response_time);
        printf("Turnaround Time for Process %d: %d\n\n", processes[i].pid, processes[i].turnaround_time);
    }

    // Print average turnaround and response times
    printf("Average Response Time: %.2f\n", total_response_time / num_processes);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / num_processes);
}

// Implement shortest remaining job first (SRJF) algorithm
void schedule_processes_SRJF(struct Process processes[], int num_processes) {
    int current_time = 0, completed = 0;
    int min_remaining_time, shortest;
    double total_turnaround_time = 0.0;
    double total_response_time = 0.0;

    // Initialize remaining times for all processes (equal to burst time)
    int remaining_time[num_processes];
    for (int i = 0; i < num_processes; i++) {
        remaining_time[i] = processes[i].burst_time;
        processes[i].started = false;
    }

    printf("\nProcess Execution (SRJF):\n");
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

        if (!processes[shortest].started) {
            processes[shortest].started = true; // Mark process as started
            processes[shortest].response_time = current_time - processes[shortest].arrival_time; // Calculate response time

            // update total response time 
            total_response_time += processes[shortest].response_time;
            printf("Response Time for Process %d: %d\n", processes[shortest].pid, processes[shortest].response_time);
        }

        // Decrement remaining time 
        remaining_time[shortest]--;

        if (remaining_time[shortest] == 0) {
            completed++;
            processes[shortest].turnaround_time = current_time + 1 - processes[shortest].arrival_time;
            printf("Turnaround Time for Process %d: %d\n\n", processes[shortest].pid, processes[shortest].turnaround_time);

            // Update total turnaround time 
            total_turnaround_time += processes[shortest].turnaround_time;
        }
        current_time++;
    }

    // Print average turnaround and response times
    printf("Average Response Time: %.2f\n", total_response_time / num_processes);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / num_processes);
}


int main() {
    int num_processes = sizeof(processes) / sizeof(struct Process);
    schedule_processes_FIFO (processes, num_processes);
    schedule_processes_SJF(processes, num_processes);
    schedule_processes_SRJF(processes, num_processes);
    return 0;
}


// The Shortest Remaining Job first algorithm performs the best in terms of turn around time because it takes 
// both the burst time and the arrival time into consideration. In comparison, the FIFO algorithm only takes 
// arrival time into account, meaning that a very small process may be stuck waiting for a large process to execute,
// even if they arrive at nearly the same time. On the other hand, the Shortest Job First alogirthm only takes 
// size into account, so if a large process were to arrive early on, its turnaround time may be super slow if 
// several smaller processes arrive at a similar time. The SRJF algorithm, however, demonstates a balance between 
// FIFO and SJF by executing large processes partially, pausing only if a process arrives which can finish executing
// before the current process. 