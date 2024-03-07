#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority; // Priority level (higher value indicates higher priority)

    int start_time;
    int remaining_time;
    bool completed;
    int last_executed_time;
};

// Example test processes
struct Process processes[] = {
    // ... (previous processes)
    {11, 10, 6, 1},
    {12, 11, 8, 3},
    {13, 12, 4, 2},
    {14, 13, 7, 1},
    {15, 14, 3, 3},
    {16, 15, 6, 2},
    {17, 16, 5, 1},
    {18, 17, 4, 3},
    {19, 18, 7, 2},
    {20, 19, 9, 1},
};

void schedule_processes(struct Process processes[], int num_processes) {
    // Separate queues for different priority levels
    struct Process high_priority_queue[10];
    struct Process medium_priority_queue[10];
    struct Process low_priority_queue[10];
    int high_size = 0, medium_size = 0, low_size = 0;

    // Distribute processes to respective queues based on priority
    for (int i = 0; i < num_processes; ++i) {
        if (processes[i].priority == 1) {
            high_priority_queue[high_size++] = processes[i];
        } else if (processes[i].priority == 2) {
            medium_priority_queue[medium_size++] = processes[i];
        } else {
            low_priority_queue[low_size++] = processes[i];
        }
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
    }

    // Execute processes from each queue
    printf("Process Execution Order:\n");

    int current_time = 0;
    double total_turnaround_time = 0.0, total_response_time = 0.0;

    // High-priority queue
    for (int i = 0; i < high_size; ++i) {
        if (i == 0) {
            high_priority_queue[i].start_time = high_priority_queue[i].arrival_time;
            current_time = high_priority_queue[i].arrival_time;
        } else {
            high_priority_queue[i].start_time = current_time;
        }
        current_time += high_priority_queue[i].burst_time;
        printf("Executing Process %d (Priority %d)\n", high_priority_queue[i].pid, high_priority_queue[i].priority);

        total_turnaround_time += current_time - high_priority_queue[i].arrival_time;
        total_response_time += high_priority_queue[i].start_time - high_priority_queue[i].arrival_time;
    }

    // Medium-priority queue
    for (int i = 0; i < medium_size; ++i) {
        if (i == 0) {
            medium_priority_queue[i].start_time = medium_priority_queue[i].arrival_time;
            current_time = medium_priority_queue[i].arrival_time;
        } else {
            medium_priority_queue[i].start_time = current_time;
        }
        current_time += medium_priority_queue[i].burst_time;
        printf("Executing Process %d (Priority %d)\n", medium_priority_queue[i].pid, medium_priority_queue[i].priority);

        total_turnaround_time += current_time - medium_priority_queue[i].arrival_time;
        total_response_time += medium_priority_queue[i].start_time - medium_priority_queue[i].arrival_time;   
    }

    // Low-priority queue
    for (int i = 0; i < low_size; ++i) {
        if (i == 0) {
            low_priority_queue[i].start_time = low_priority_queue[i].arrival_time;
            current_time = low_priority_queue[i].arrival_time;
        } else {
            low_priority_queue[i].start_time = current_time;
        }
        current_time += low_priority_queue[i].burst_time;
        printf("Executing Process %d (Priority %d)\n", low_priority_queue[i].pid, low_priority_queue[i].priority);
        
        total_turnaround_time += current_time - low_priority_queue[i].arrival_time;
        total_response_time += low_priority_queue[i].start_time - low_priority_queue[i].arrival_time;
    }

    printf("Average Turnaround Time: %.2f", total_turnaround_time / num_processes);
    printf("Average Response Time: %.2f", total_response_time / num_processes);  
}

int main() {
    int num_processes = sizeof(processes) / sizeof(struct Process);
    schedule_processes(processes, num_processes);
    return 0;
}
