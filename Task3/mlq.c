#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int start_time;
    int completion_time;
    int remaining_time; 
    bool started; 
};

struct Process processes[] = {
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
    struct Process high_priority_queue[10];
    struct Process medium_priority_queue[10];
    struct Process low_priority_queue[10];
    int high_size = 0, medium_size = 0, low_size = 0;
    int time_slice = 4;  
    int current_time = 0;
    int total_high_turnaround_time = 0, total_med_turnaround_time = 0, total_low_turnaround_time = 0;
    int total_high_response_time = 0, total_med_response_time = 0, total_low_response_time = 0;

    // Distribute processes to respective queues based on priority
    for (int i = 0; i < num_processes; ++i) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].started = false;
        if (processes[i].priority == 1) {
            high_priority_queue[high_size++] = processes[i];
        } else if (processes[i].priority == 2) {
            medium_priority_queue[medium_size++] = processes[i];
        } else {
            low_priority_queue[low_size++] = processes[i];
        }
    }

    printf("Process Execution Order:\n");

    // Execute high-priority queue with FCFS
    for (int i = 0; i < high_size; ++i) {
        // update current time if needed 
        if (current_time < high_priority_queue[i].arrival_time) {
            current_time = high_priority_queue[i].arrival_time;
        }
        high_priority_queue[i].start_time = current_time;  // update start time to current time 
        current_time += high_priority_queue[i].burst_time; // update current time (execute process)
        high_priority_queue[i].completion_time = current_time;  // completion time

        // Calculate turnaround and response times 
        int turnaround_time = high_priority_queue[i].completion_time - high_priority_queue[i].arrival_time;
        int response_time = high_priority_queue[i].start_time - high_priority_queue[i].arrival_time;
        total_high_turnaround_time += turnaround_time;
        total_high_response_time += response_time;

        printf("Executing Process %d (Burst Time: %d, Priority: %d)\n", high_priority_queue[i].pid, high_priority_queue[i].burst_time, high_priority_queue[i].priority);
        printf("Turnaround Time for Process %d: %d\n\n", high_priority_queue[i].pid, turnaround_time);
    }

    // Round Robin scheduling for medium-priority queue
    bool done = false; // bool to keep track of when a process is completed 
    while (!done) {
        done = true; // assume true 
        for (int i = 0; i < medium_size; ++i) {
            if (medium_priority_queue[i].remaining_time > 0) {
                done = false; // There is still a process that needs to be executed
                // if process hasnt started yet 
                if (!medium_priority_queue[i].started) {
                    medium_priority_queue[i].start_time = current_time; // set start time equal to current time 
                    medium_priority_queue[i].started = true; 
                }
                if (medium_priority_queue[i].remaining_time > time_slice) {
                    current_time += time_slice;   // add time slice to current time
                    medium_priority_queue[i].remaining_time -= time_slice;  // subtract time slice from remaining time
                } else {
                    current_time += medium_priority_queue[i].remaining_time;    // add remaining time to current time 
                    medium_priority_queue[i].completion_time = current_time;    // completion time
                    medium_priority_queue[i].remaining_time = 0;    // set remaining time to zero

                    // Calculate turnaround and response time 
                    int turnaround_time = medium_priority_queue[i].completion_time - medium_priority_queue[i].arrival_time;
                    int response_time = medium_priority_queue[i].start_time - medium_priority_queue[i].arrival_time;
                    total_med_turnaround_time += turnaround_time;
                    total_med_response_time += response_time;

                    
                }
                printf("Executing Process %d (Burst Time: %d, Priority: %d)\n", medium_priority_queue[i].pid, medium_priority_queue[i].burst_time, medium_priority_queue[i].priority);
                printf("Turnaround Time for Process %d: %d\n\n", medium_priority_queue[i].pid, medium_priority_queue[i].completion_time - medium_priority_queue[i].arrival_time);
            }
        }
    }

    // Execute low-priority queue 
    for (int i = 0; i < low_size; ++i) {
        // update current time 
        if (current_time < low_priority_queue[i].arrival_time) {
            current_time = low_priority_queue[i].arrival_time;
        }
        // set start time to current time 
        low_priority_queue[i].start_time = current_time;
        // Increment current time by current processes burst time 
        current_time += low_priority_queue[i].burst_time;
        // Set completion time to current time 
        low_priority_queue[i].completion_time = current_time;

        // Calculate turnaround time and response time 
        int turnaround_time = low_priority_queue[i].completion_time - low_priority_queue[i].arrival_time;
        int response_time = low_priority_queue[i].start_time - low_priority_queue[i].arrival_time;
        total_low_turnaround_time += turnaround_time;
        total_low_response_time += response_time;

        printf("Executing Process %d (Burst Time: %d, Priority: %d)\n", low_priority_queue[i].pid, low_priority_queue[i].burst_time, low_priority_queue[i].priority);
        printf("Turnaround Time for Process %d: %d\n\n", low_priority_queue[i].pid, turnaround_time);
    }
    int total_turnaround_time = total_high_turnaround_time + total_med_turnaround_time + total_low_turnaround_time;
    int total_response_time = total_high_response_time + total_med_response_time + total_low_response_time;

     // Calculate and print average turnaround and response times
    printf("Average High Priority Turnaround Time: %.2f\n", (float)total_high_turnaround_time / high_size);
    printf("Average High Priority Response Time: %.2f\n\n", (float)total_high_response_time / high_size);

    printf("Average Medium Priority Turnaround Time: %.2f\n", (float)total_med_turnaround_time / medium_size);
    printf("Average Medium Priority Response Time: %.2f\n\n", (float)total_med_response_time / medium_size);

    printf("Average Low Priority Turnaround Time: %.2f\n", (float)total_low_turnaround_time / low_size);
    printf("Average Low Priority Response Time: %.2f\n\n", (float)total_low_response_time / low_size);

    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / num_processes);
    printf("Average Response Time: %.2f\n\n", (float)total_response_time / num_processes);
}

int main() {
    int num_processes = sizeof(processes) / sizeof(struct Process);
    schedule_processes(processes, num_processes);
    return 0;
}
