<!-- omit in toc -->

# Lab 6

In this lab, you will gain familiarity with many concepts pertinent to operating systems and C programming:

- Linked list data structure
- OS scheduling algorithms
  - First come first served (FCFS)
  - Priority queue
    - Priority value is used by the scheduling algorithm to determine which tasks to focus on first.
    - For example, an OS would likely give high priority to I/O operations because it's important that the CPU reacts as soon as you type a key.
    - A long download may have low priority.
  - Round robin
- C structs
- Pointers
- Memory allocation and deallocation

In particular, this lab's goals are

1. Become familiar with the `task_struct` that is used by the OS to manage a program running in memory. Here, we'll use only a subset of fields found in the real Linux `task_struct`, namely the _process id_ (pid) and _priority_. If interested, you can view the Linux kernel's real `task_struct` in the [sched.h](https://github.com/torvalds/linux/blob/master/include/linux/sched.h) header file distributed in the newest [Linux kernel code](https://github.com/torvalds/linux). Typically, the pid and priority values are assigned by the OS, but in this lab, you'll simulate this OS operation by manually assigning values to the `task_struct` fields.
2. Gain experience with **singly linked list** in C (code provided), one of the fundamental data structures used in operating systems (and in general). Each element in the linked list is a `task_struct`. A linked list is a suitable data structure choice because of its efficient use of memory and $O(1)$ queue operations (enqueue and dequeue) and stack operations (push and pop). However, a linked list has some disadvantages that you'll soon recall or become familiar with.
3. Simulate **priority queue**, **first come first serve** (**FCFS**) and **round robin** scheduling algorithms.

<details open>
    <summary>Contents</summary>

- [Pre-lab knowledge](#pre-lab-knowledge)
  - [Background reading](#background-reading)
  - [Structure](#structure)
- [Part 0: Understand starter code](#part-0-understand-starter-code)
- [Part 1. Min heapify](#part-1-min-heapify)
  - [Testing](#testing)
- [Part 2. Scheduling algorithms](#part-2-scheduling-algorithms)
  - [Testing](#testing-1)
- [Submit your assignment](#submit-your-assignment)

</details>

## Pre-lab knowledge

### Background reading

- For linked lists and list operations, [Linked List Basics](http://cslibrary.stanford.edu/103/LinkedListBasics.pdf)
- For a review of binary heaps and the heapify algorithm, [Heaps.pdf](Heaps.pdf) included in this repo
- For a few OS scheduling algorithms, [OSTEP Chapter 7](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched.pdf)
- C concepts:
  - For how header files work in C, chapter 4.5 in _The C Programming Language_
  - For pointers, memory allocation, and deallocation, chapter 5 in _The C Programming Language_
  - For information about structs, chapter 6 in _The C Programming Language_

### Structure

Here is a description of each file and what you are expected to do (if anything) in each:

```
.
├── Heaps.pdf - Background reading about heaps
├── Makefile
├── README.md
├── main.c - Do not modify. Contains main function
├── schedule.c - Contains functions that simulate running and scheduling tasks. Implement run_to_completion, run_with_quantum, fcfs, priority_queue, round_robin
├── schedule.h
├── task.c - Contains linked list functions (code given) and min_heapify function (TODO). Read through task.h to see function prototypes for given functions, then implement min_heapify
├── task.h - Contains definition of task_struct and function prototypes for task.c. Read the prototypes to understand given code, which is necessary to complete task.c and schedule.c
└── tests - Test data
    ├── part1
    └── part2
```

In `task.h`, you will find the definition of `task_struct`, which contains data (`priority`, `pid`, `remaining_cycles`) and pointer `next`.

There are several comments and docstrings in the source files that will guide you through the assignment.

Lastly, in this lab, you **may not** add or remove additional global variables. **If this is done, points will be deducted.** Ask your cohort leader for clarification if you have any questions regarding this stipulation.

## Part 0: Understand starter code

You are provided code for all necessary linked list functions in `task.c`. You probably will not need to use all of the functions.

In `task.h`, read the definition of `task_struct` and the linked list function prototypes to see how to work with the singly linked list. There should be no need to carefully read the code for the linked list operations in `task.c`, but you may if you want.

## Part 1. Min heapify

In `task.c`, implement the `min_heapify` function to convert the linked list data structure to a priority queue for use in the priority-based scheduling algorithm. Read `Heaps.pdf` to learn or refamiliarize yourself with the min heapify algorithm. The pseudocode given is for a max heap, but the code for a min heap is very similar.

A docstring is provided in `task.h`.

### Testing

Run `make`, then run the program with `./main`.

The `main` function accepts input from `stdin` and outputs to `stdout` (no CLI args). An example run is as follows:

```text
Number of tasks: 4
pid priority cycles: 12 50 100
pid priority cycles: 13 1 80
pid priority cycles: 14 40 60
pid priority cycles: 15 0 40
---- Tasks ----
(num_tasks) [pid:priority:cycles:priority/cycles ...]
(4) [ 12:50:100:0.50 13:1:80:0.01 14:40:60:0.67 15:0:40:0.00 ]
Select scheduling algorithm (0: Display min heap, 1: FCFS, 2: Priority queue, 3: Round robin): 0
---- Min heap ----
(4) [ 15:0:40:0.00 13:1:80:0.01 14:40:60:0.67 12:50:100:0.50 ]
```

First, input the number of tasks and the data for each task. Then, select the scheduling algorithm. In this case, since the scheduling algorithms have not been implemented yet, select 0 to display your min heap to check whether it is correct.

Notice that the task with the minimum priority ratio (defined as `priority / cycles`) is at the front of the min heap, as expected. However, 0.67 is before 0.50 even though `0.50 < 0.67`. Recall from COMP 210 that this is intended behavior because a min heap guarantees only that all paths from a root to a leaf are in ascending order.

There are some other test inputs and outputs in `tests/part1`, and you can check for differences with `diff`. The commands to do so are similar to the ones in previous labs (e.g., `./main < input.txt > output.txt` and `diff expected.txt output.txt`).

## Part 2. Scheduling algorithms

In this part, you will simulate a few scheduling algorithms to see how an OS schedules and runs tasks on a CPU. We will implement first come first serve (FCFS), priority-based scheduling, and round robin. See [Background reading](#background-reading) and the docstrings in `schedule.h` for information about these algorithms.

For the scheduling algorithms, pseudocode is provided in `schedule.h`. Additionally, example runs for each scheduling algorithm are shown in the sample test outputs in [tests/part2](tests/part2).

In `schedule.c`, implement the following functions:

- `run_to_completion`
- `run_with_quantum`
- `fcfs`
- `priority_queue`
- `round_robin`

### Testing

This section can be tested similarly to the previous section. Sample inputs and outputs for the various scheduling algorithms are in `tests/part2`. The inputs are nearly identical to those in `tests/part1`, and the only difference is the very last number, which selects the scheduling algorithm (i.e., now 1, 2, and 3 for FCFS, priority queue, and round robin, respectively).

## Submit your assignment

1. Use git to push your finished code to this GitHub repository.
2. Go to the COMP 211 course in Gradescope and click on the assignment called **Lab 6**.
3. Click on the option to **Submit Assignment** and choose GitHub as the submission method.
4. You should see a list of your public repositories. Select the one named **lab-06-yourname** and submit it.
5. Your assignment should be autograded within a few seconds and you will receive feedback for the autograded portion.
6. If you receive all the points, then you have completed this lab! Otherwise, you are free to keep pushing commits to your GitHub repository and submit for regrading up until the deadline of the lab.
