## 🍽️ Philosophers – Multithreading & Synchronization

**Philosophers** is a foundational 42 project focused on exploring the concepts of **concurrency, threads, and synchronization** using the classic *Dining Philosophers* problem as the main challenge.

The project simulates a group of philosophers who alternately think, eat, and sleep — while sharing a limited number of resources. The goal is to prevent **deadlocks**, **race conditions**, and **starvation**, ensuring each philosopher can eat without conflict.

### 🎯 Project Objectives

* Learn how to create and manage **threads**
* Implement **mutexes** for safe shared resource access
* Prevent **deadlocks**, **data races**, and **starvation**
* Handle **timing and synchronization** with precision

### 🛠 Key Features

* Multithreaded simulation using **pthreads**
* Configurable number of philosophers and timing parameters
* Accurate time tracking and logging
* Robust fork access logic using **mutexes**

### ⚙️ Prerequisites

* GCC/Clang compiler with C99 support
* pthreads library (standard on Linux/macOS)
* Good understanding of:

  * C programming
  * Threads and mutexes
  * Time management in concurrent applications

### 💡 What I Learned

* Hands-on experience with **low-level multithreading**
* Using **mutexes** and **synchronization primitives** correctly
* Dealing with complex timing issues in concurrent systems
* Designing clean, safe, and efficient parallel logic
