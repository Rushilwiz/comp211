// PID: 730677144
// I pledge the COMP 211 honor code.

#include <stdio.h>
#include <stdlib.h>

#include "schedule.h"
#include "task.h"

void run_to_completion(task_struct* task) {
    printf("Task %d ran for %d cycles.\n", task->pid, task->remaining_cycles);
    task->remaining_cycles = 0;
    printf("Task %d completed.\n", task->pid);
}

void run_with_quantum(task_struct* task, unsigned int quantum) {
    if (task->remaining_cycles <= quantum) {
        run_to_completion(task);
    } else {
        printf("Task %d ran for %d cycles.\n", task->pid, quantum);
        task->remaining_cycles -= quantum;
    }
}

void fcfs() {
    while (get_task(0) != NULL) {
        run_to_completion(remove_task(get_task(0)->pid));
    }
}

/**
 * While the queue is not empty:
 *  - Min heapify the linked list.
 *  - Get the highest priority task from the list (the one at the head).
 *  - Remove and run the highest priority task for the given quantum.
 *  - If the task is not complete, then append it to the linked list.
 */

void priority_queue(unsigned int quantum) {
    while (get_task(0) != NULL) {
        if (size() > 1)
            min_heapify();

        task_struct* task = remove_task(get_task(0)->pid);
        run_with_quantum(task, quantum);

        if (task->remaining_cycles != 0) {
            append_task(task->pid, task->priority, task->remaining_cycles);
        } else {
            free(task);
        }
    }
}

void round_robin(unsigned int quantum) {
    while (head != NULL) {
        task_struct* task = head;
        head = head->next;
        run_with_quantum(task, quantum);

        if (task->remaining_cycles > 0) {
            append_task(task->pid, task->priority, task->remaining_cycles);
        } else {
            free(task);
        }

        if (head == NULL) {
            tail = NULL;
        }
    }
}
