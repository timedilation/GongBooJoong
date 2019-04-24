# Introduction
## Operating System Roles
- Referee: resource allocation, isolation, communication
- Illusionist: use entire machine, infinite processors/memory, reliable storage/network
- Glue: libraries, user interface widgets, ...
## Operating System Abstractions
- processes and threads: abstraction for a running program. single core-run concurrently with context-switching
- virtual memory: abstraction of the physical memory. exclusive use of main memory(illusion). +MMU
- files: sequence of bytes.
## OS Challenges
- Reliability, Availability, Security, Privacy
- Portability, Performance
# Kernel Abstraction
## Process
- an instance of a program, running with limited rights
- roles: execution, protection
- OS keeps track of process uwing PCB
## Mode Switch
- User Mode to Kernel Mode
    + Interrupts, Exceptions, System calls
- Kernel Mode to User Mode
    + New process/thread starts
    + return from interrupt, exception, system call
    + context switch
    + user-level upcall (UNIX signal)
### Interrupts
- signal that are sent across IRQ (Interrupt Request
Line) by a hardware or software
- **Interrupt Vector Table**: Table set up by OS kernel; pointers to code to run on different events
- **Interrupt Stack**: Per-processor, located in kernel (not user) memory
### System Call
- abstracted interface for user space
- ensures system security and stability
### Upcall
- User-level event delivery: notify user process of some event that needs to be handled right away
- AKA Unix Signal
### Upcalls vs Interrupts
- Signal handlers = interrupt vector handlers
- Signal stack = interrupt stack
- Automatic save/restore registers = transparent resume
- Signal masking: signals disabled while in signal handler
# Synchronization
- **Race condition**: output of a concurrent program depends on the order of operations between threads
## Critical Section
- a segment of code that requires atomically accessing shared state (or resource) No more than one thread in critical section at a time
- **Safety (aka mutual exclusion)**: no more than one thread in critical section at a time
- **Liveness (aka progress)**: If multiple threads simultaneously request to enter critical section, must allow one to proceed
- **Bounded waiting (aka starvation-free)**: Must eventually allow waiting thread to proceed
- **Efficient**: don’t consume too much resource while waiting
- **Fair**: don’t make one thread wait longer than others. Hard to do efficiently
- 
