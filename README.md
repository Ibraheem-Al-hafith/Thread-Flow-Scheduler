
---

# 🚀 ThreadFlow-Scheduler: Multi-Threaded Task Processor

## 🎓 Context

Developed for the **Operating Systems** course at the **University of Khartoum**. This project showcases advanced concurrency, thread synchronization, and real-time task scheduling.

---

## 📖 Project Overview

This system simulates a high-performance multi-unit processing environment. Tasks are parsed from a file, entered into a global queue, and then navigated through a series of specialized worker threads (Units 0-4) based on a custom itinerary.

## 🏗️ System Architecture

The engine runs on three primary thread types:

* 📥 **Receptor**: The gatekeeper. It reads tasks from the input file and introduces them to the **Waiting Queue**.


* 🚦 **Dispatcher**: The traffic controller. It monitors the queue and routes tasks to their next required processing unit.


* ⚙️ **Processing Units**: 5 specialized worker threads (0-4) that perform unique mathematical transformations or output tasks.



---

## 🛠️ Key Features

* 🔒 **Thread Synchronization**: Robust use of **Mutexes** and **Condition Variables** to prevent race conditions in shared queues.
* 🔢 **Modulo Arithmetic**: Secure computation using a constant  for all unit operations.


* ⏱️ **Timing Logic**: High-precision task arrival tracking using `gettimeofday()`.


* 💤 **Cooldown Simulation**: Units simulate real-world hardware constraints by sleeping for **0.5s** after each operation.



---

## 📂 Project Structure

```bash
ThreadFlow-OS/
├── 📁 include/
│   └── project.h       # 📜 Shared types & function headers
├── 📁 src/
│   ├── main.c          # 🏁 Thread init & sync logic
│   ├── receptor.c      # 📑 File parsing logic
│   ├── dispatcher.c    # 🎯 Task routing engine
│   └── units.c         # 🧮 Math operations (Units 0-4)
├── 📁 docs/
    └── Project-All.pdf  # 📘 Course instructions [cite: 2]
├── 🔨 Makefile         # ⚡ Automation for building
└── 🚫 .gitignore       # 🧹 Clean repository management

```

---

## ⚙️ Unit Operations Table

| Unit | Operation | Description |
| --- | --- | --- |
| **0** | `+7 % M` | Addition & Modulo 
| **1** | `*2 % M` | Multiplication & Modulo 
| **2** | `^5 % M` | Power & Modulo 
| **3** | `-19` | Subtraction 
| **4** | `Print` | Final Result Output 

---

## 🚀 Getting Started

### 📋 Prerequisites

* **GCC** compiler
* **Pthread** library (POSIX threads)

### 💻 Installation & Execution

1. **Clone the repo:**
```bash
git clone https://github.com/Ibraheem-Al-hafith/Thread-Flow-Scheduler.git

```


2. **Compile the engine:**
```bash
make

```


3. **Run the simulation:**
```bash
./system_sim input_file.txt

```



---

## 👥 The Team

* 🧬 **Member 1**: [Name] — *Concurrency & Synchronization*
* 📂 **Member 2**: [Name] — *File I/O & Receptor Logic*
* 🎮 **Member 3**: [Name] — *Dispatcher & Unit Operations*

---
