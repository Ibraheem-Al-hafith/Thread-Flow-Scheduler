# Thread-Flow-Scheduler: Multi-Threaded Task Processor

## 📌 Project Overview
[cite_start] Developed for the Operating Systems course at the **University of Khartoum**. [cite_start]This system simulates a multi-unit processing environment where tasks are read from a file, queued, and dispatched to specific worker threads (Units 0-4) based on a predefined itinerary[cite: 24, 68].

## 🏗 System Architecture
The system consists of the following components implemented as concurrent threads:
* [cite_start]**Receptor**: Reads tasks from an input file and adds them to the main Waiting Queue[cite: 36, 68].
* [cite_start]**Dispatcher**: Manages task movement between the Waiting Queue and specific Unit Queues[cite: 69].
* [cite_start]**Processing Units**: 5 threads that perform mathematical operations (+7, *2, ^5, -19, and Print)[cite: 70, 71].

## 🛠 Features
- **Thread Synchronization**: Uses Mutexes and Condition Variables for thread-safe queue management.
- [cite_start]**Modulo Arithmetic**: All operations are performed modulo $M=10,000$[cite: 73].
- [cite_start]**Timing Logic**: Precise arrival tracking using `gettimeofday()`[cite: 36].
- [cite_start]**Cooldown Simulation**: Each unit sleeps for 0.5s after task execution to simulate real-world processing[cite: 72].

## 🚀 Getting Started
### Prerequisites
- GCC compiler
- Pthread library

### Installation & Execution
1. Clone the repository:
   `git clone https://github.com/your-username/ThreadFlow-OS.git`
2. Compile the project:
   `make`
3. Run the simulator:
   `./system_sim input_file.txt`

## 👥 The Team
- Member 1: [Name] - Concurrency & Synchronization
- Member 2: [Name] - File I/O & Receptor Logic
- Member 3: [Name] - Dispatcher & Unit Operations
