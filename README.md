# Batch Scheduling Simulator

[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/mafizurrahman/Batch-Scheduling-Simulator-)

A comprehensive batch scheduling simulator implemented in C that demonstrates the performance of various CPU scheduling algorithms. The simulator provides insights into different scheduling strategies through practical implementation and performance analysis.

## Features

- Implementation of four popular scheduling algorithms:
  - **FIFO** (First-In-First-Out)
  - **SJF** (Shortest Job First)
  - **SRT** (Shortest Remaining Time)
  - **Round Robin**
- Performance metrics calculation (turnaround time, waiting time)
- Configurable simulation parameters
- Random process generation with customizable attributes

## Getting Started

### Prerequisites

- GCC Compiler
- Make (optional)
- Unix-like environment (Linux/MacOS) or Windows with GCC installed

### Installation

1. Clone the repository
```bash
git clone https://github.com/mafizurrahman/Batch-Scheduling-Simulator-.git
cd Batch-Scheduling-Simulator-
```

2. Compile the source code
```bash
gcc project.c -o batch_scheduler
```

3. Run the simulator
```bash
./batch_scheduler
```

## Scheduling Algorithms

### 1. FIFO (First-In-First-Out)
- Non-preemptive scheduling
- Processes are executed in arrival order
- Simple implementation but may lead to convoy effect

### 2. SJF (Shortest Job First)
- Non-preemptive scheduling
- Processes are executed based on total CPU burst time
- Optimal for minimizing average waiting time
- May lead to starvation of longer processes

### 3. SRT (Shortest Remaining Time)
- Preemptive version of SJF
- Processes can be interrupted by shorter jobs
- Better average response time than SJF
- Higher scheduling overhead

### 4. Round Robin
- Time-quantum based preemptive scheduling
- Fair CPU distribution among processes
- Suitable for time-sharing systems
- Performance depends on quantum size selection

## Implementation Details

### Key Functions

| Function | Description |
|----------|-------------|
| `initialize_processes()` | Initializes process attributes with random values |
| `run_simulation()` | Executes simulation for specified algorithm |
| `compute_avg_tt()` | Calculates average turnaround time |
| `compute_avg_wt()` | Calculates average waiting time |
| `print_processes()` | Displays process attributes |
| `are_active_processes()` | Checks for remaining active processes |

### Parameters

- **d**: Mean CPU burst time
- **v**: Variability percentage of CPU burst time
- **n**: Number of processes
- **k**: Range of arrival times

## Performance Analysis

The simulator evaluates each algorithm based on:
1. Average Turnaround Time
2. Average Waiting Time
3. CPU Utilization
4. Throughput

## Sample Output

```
Simulation Results:
-----------------
Algorithm: FIFO
Avg Turnaround Time: 245.6 ms
Avg Waiting Time: 125.3 ms

Algorithm: SJF
Avg Turnaround Time: 198.2 ms
Avg Waiting Time: 78.9 ms

Algorithm: SRT
Avg Turnaround Time: 185.4 ms
Avg Waiting Time: 65.7 ms

Algorithm: Round Robin (q=20)
Avg Turnaround Time: 215.8 ms
Avg Waiting Time: 95.6 ms
```
