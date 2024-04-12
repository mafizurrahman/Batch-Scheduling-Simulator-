# Batch-Scheduling-Simulator-
This is a batch scheduling simulator written in C. It simulates the performance of three different batch scheduling algorithms:  FIFO (First-In-First-Out), SJF (Shortest Job First), and SRT (Shortest Remaining Time). Additionally, it includes an interactive  processing algorithm called Round Robin.

# How to Compile 
1. Download the project.c file. Open any terminal for compiling the C code. 
2. Compile the code using a C compiler. For example, you can use GCC: gcc project.c -o batch_scheduling_simulator 
3. Run the compiled executable: ./batch_scheduling_simulator

# Algorithms Implemented 
1. FIFO (First-In-First-Out): Processes are executed in the order they arrive. No preemption is involved. 
2. SJF (Shortest Job First): Processes are executed in order of their total CPU time. Shorter jobs are prioritized. 
3. SRT (Shortest Remaining Time):  If a shorter job arrives while a process is running, it is interrupted. 
4. Round Robin: Each process gets a small unit of CPU time (time quantum). After this time, the process is preempted 
and added to the end of the ready queue.

# Functions 
• print_processes: Prints the attributes of all processes. 
• run_fifo, run_sjf, run_srt, run_rr: Functions implementing each scheduling algorithm. 
• compute_avg_tt: Computes the average turnaround time of all processes. 
• compute_avg_wt: Computes the average waiting time of all processes. 
• initialize_processes: Initializes the attributes of processes with random values. 
• are_active_processes: Checks if there are any active processes left to execute. 
• run_simulation: Runs the simulation for a given scheduling algorithm. 

# Results 
The program simulates different combinations of parameters (d and v) and measures the average turnaround time and 
average waiting time for each scheduling algorithm. The results are printed for analysis. 
 
# Additional Notes 
• The d parameter represents the mean of total CPU time, while v represents the variability as a percentage of d. 
• The simulation assumes a fixed number of processes (n) and a fixed range of arrival times (k). 
• The code includes error handling for negative values of d and ensures that the turnaround time is positive. 
