#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define MAX_PROCESSES 100
#define MAX_ARRIVAL_TIME 1000

typedef struct process {
    int active;
    int arrival_time;
    int total_cpu_time;
    int remaining_cpu_time;
    int turnaround_time;
    int waiting_time;
} process_t;

int rand_uniform(int a, int b) {
    return rand() % (b - a + 1) + a;
}

int rand_normal(int mean, int stddev) {
    double u1 = rand() / (double)RAND_MAX;
    double u2 = rand() / (double)RAND_MAX;
    double z = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
    return mean + (int)(stddev * z);
}

void print_processes(process_t processes[], int n) {
    printf("Process  Active  Arrival Time  Total CPU Time  Remaining CPU Time  Turnaround Time  Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%-8d %-7d %-13d %-16d %-20d %-15d %-13d\n",
            i, processes[i].active, processes[i].arrival_time,
            processes[i].total_cpu_time, processes[i].remaining_cpu_time,
            processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\n");
}

void run_fifo(process_t processes[], int n, int time) {
    for (int i = 0; i < n; i++) {
        if (processes[i].active == 1) {
            processes[i].remaining_cpu_time--;
            if (processes[i].remaining_cpu_time == 0) {
                processes[i].active = 0;
                processes[i].turnaround_time = time - processes[i].arrival_time;
            }
            break;
        }
    }
}

void run_sjf(process_t processes[], int n, int time) {
    int shortest = -1;
    for (int i = 0; i < n; i++) {
        if (processes[i].active == 1) {
            if (shortest == -1 || processes[i].remaining_cpu_time < processes[shortest].remaining_cpu_time) {
                shortest = i;
            }
        }
    }
    if (shortest != -1) {
        processes[shortest].remaining_cpu_time--;
        if (processes[shortest].remaining_cpu_time == 0) {
            processes[shortest].active = 0;
            processes[shortest].turnaround_time = time - processes[shortest].arrival_time;
        }
    }
}

void run_srt(process_t processes[], int n, int time) {
    int shortest_index = -1;
    int shortest_time = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (processes[i].active && processes[i].arrival_time <= time && processes[i].remaining_cpu_time < shortest_time) {
            shortest_index = i;
            shortest_time = processes[i].remaining_cpu_time;
        }
    }
    if (shortest_index != -1) {
        processes[shortest_index].remaining_cpu_time--;
        if (processes[shortest_index].remaining_cpu_time == 0) {
            processes[shortest_index].active = 0;
            processes[shortest_index].turnaround_time = time - processes[shortest_index].arrival_time;
        }
    }
}


void run_rr(process_t processes[], int n, int time) {
    // Define the time quantum for Round Robin
    const int time_quantum = 3; // Time quantum as needed

    static int current_process = 0; // Static variable to keep track of the current process

    for (int i = 0; i < n; i++) {
        // Find the next active process
        current_process = (current_process + 1) % n;
        if (processes[current_process].active) {
            // Execute the process for the time quantum or remaining CPU time, whichever is smaller
            int execution_time = fmin(time_quantum, processes[current_process].remaining_cpu_time);
            processes[current_process].remaining_cpu_time -= execution_time;

            // Update the time
            time += execution_time;

            // If the process has finished, update its attributes
            if (processes[current_process].remaining_cpu_time == 0) {
                processes[current_process].active = 0;
                processes[current_process].turnaround_time = time - processes[current_process].arrival_time;
            }
            break; // Exit the loop after executing one process
        }
    }
}



float compute_avg_tt(process_t processes[], int n) {
    float sum_tt = 0;
    for (int i = 0; i < n; i++) {
        sum_tt += processes[i].turnaround_time;
    }
    return sum_tt / n;
}

float compute_avg_wt(process_t processes[], int n) {
    float sum_wt = 0;
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].total_cpu_time;
        sum_wt += processes[i].waiting_time;
    }
    return sum_wt / n;
}

void initialize_processes(process_t processes[], int n, int k, int d, float v) {
    for (int i = 0; i < n; i++) {
        processes[i].active = 1;
        processes[i].arrival_time = rand_uniform(0, k);
        processes[i].total_cpu_time = rand_normal(d, d * v);
        processes[i].remaining_cpu_time = processes[i].total_cpu_time;
    }
}

int are_active_processes(process_t processes[], int n) {
    for (int i = 0; i < n; i++) {
        if (processes[i].active == 1) {
            return 1;
        }
    }
    return 0;
}

float run_simulation(process_t processes[], int n, int k, void (*scheduler)(process_t[], int, int)) {
    int time = 0;
    while (are_active_processes(processes, n)) {
        scheduler(processes, n, time);
        time++;
    }
    return compute_avg_tt(processes, n);
}

int main() {
    srand(time(0));

    // Define ranges for d and v
    const int num_d_values = 10;
    const int d_values[] = {51, 52, 53, 54, 55, 56, 57 , 58,59,60};
    const int num_v_values = 1;
    const float v_percentages[] = { 0.2}; // v as a percentage of d

    // Initialize processes array
    const int n = 100;
    const int k = 1000;
    process_t processes[n];

    // Perform simulation for different combinations of d and v
    for (int i = 0; i < num_d_values; i++) {
        for (int j = 0; j < num_v_values; j++) {
            // Initialize processes with current d and v values
            initialize_processes(processes, n, k, d_values[i], v_percentages[j]);


             // Check if d value is negative
         /*   if (d_values[i] < 0) {
                printf("Error: Negative d value encountered for d = %d\n", d_values[i]);
                continue; // Skip this combination and proceed to the next one
            } */



            // Run simulation with FIFO scheduling algorithm
            float fifo_att = run_simulation(processes, n, k, run_fifo);
            float fifo_awt = compute_avg_wt(processes, n);


            // Check if turnaround time is positive for FIFO
       /*     if (fifo_att < 0) {
                printf("Error: Negative FIFO turnaround time for d = %d\n", d_values[i]);
                continue; // Skip further processing for this combination
            }*/



            // Run simulation with SJF scheduling algorithm
            initialize_processes(processes, n, k, d_values[i], v_percentages[j]); // Reset processes
            float sjf_att = run_simulation(processes, n, k, run_sjf);
            float sjf_awt = compute_avg_wt(processes, n);

            // Run simulation with SRT scheduling algorithm
            initialize_processes(processes, n, k, d_values[i], v_percentages[j]); // Reset processes
            float srt_att = run_simulation(processes, n, k, run_srt);
            float srt_awt = compute_avg_wt(processes, n);

             // Run simulation with Round Robin scheduling algorithm
            initialize_processes(processes, n, k, d_values[i], v_percentages[j]); // Reset processes
            float rr_att = run_simulation(processes, n, k, run_rr);
            float rr_awt = compute_avg_wt(processes, n);

            // Print or use the results as needed
            printf("For d = %d and v = %.2f:\n", d_values[i], v_percentages[j]);
            printf("FIFO average turnaround time: %.2f\n", fifo_att);

            printf("SJF average turnaround time: %.2f\n", sjf_att);

            printf("SRT average turnaround time: %.2f\n", srt_att);
            printf("Round Robin avg. turnaround time: %.2f\n", rr_att);

            printf("------------Waiting Time------------");

            printf("\n");

            printf("FIFO average waiting time: %.2f\n", fifo_awt);
            printf("SJF average waiting time: %.2f\n", sjf_awt);

            printf("SRT average waiting time: %.2f\n", srt_awt);

            printf("Round Robin average waiting time: %.2f\n", rr_awt);


            printf("\n");
        }
    }

    return 0;
}
