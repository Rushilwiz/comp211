// Do not edit this file

#include <math.h>
#include <stdbool.h>

#ifndef _TASK_H_
#define _TASK_H_

#define EPSILON 0.0001

typedef struct task_struct {
    unsigned int priority;          // lower value means higher priority
                                    // priority ratio used in min heap is
                                    // priority / remaining_cycles
    unsigned int pid;               // process id
    unsigned int remaining_cycles;  // remaining CPU cycles needed to complete
                                    // this task. set this to 0 if there would
                                    // be underflow when subtracting. do not set
                                    // to a "negative" number!
    struct task_struct* next;
} task_struct;

/**
 * Removes all task_structs in the linked list
 * (i.e., size = 0 after calling this function).
 *
 * Deallocates memory used by each task_struct
 *
 * @return void
 */
void clear();

/**
 * @return number of task_structs in the linked list
 */
unsigned int size();

/**
 * Create and initialize a new task_struct with the given pid, priority, and
 * cycles arguments
 *
 * And append the task_struct to the end of the linked list
 *
 * @param pid
 * @param priority
 * @param cycles
 * @return true (success) | false (failure, i.e., duplicate pid in the linked
 * list)
 */
bool append_task(unsigned int pid, unsigned int priority, unsigned int cycles);

/**
 * Create and initialize a new task_struct with the given pid, priority, and
 * cycles arguments
 *
 * And insert the new task_struct at the given index position
 *
 * Shifts the task_struct currently at specified index position (if any) and any
 * successors to the right, effectively adding 1 to their index positions.
 *
 * @param index index to insert new task_struct at (i.e., after insertion, the
 * new task_struct will be at this index)
 * @param pid
 * @param priority
 * @param cycles
 * @return true (success) | false (failure, i.e., duplicate pid or index out of
 * range (index > size())
 */
bool insert_task(unsigned int index,
                 unsigned int pid,
                 unsigned int priority,
                 unsigned int cycles);

/**
 * Change the location of an existing task_struct (given pid) in the linked list
 * to the specified index.
 *
 * Shifts the task_struct currently at specified index position (if any) and any
 * successors to the right, effectively adding 1 to their index positions.
 *
 * This is accomplished via a call to remove_task and insert_task.
 * See the docstring for insert_task to see how shifting of other task_structs
 * is handled.
 *
 * @param index index to set new task_struct to (i.e., after set, the new
 * task_struct will be at this index)
 * @param pid
 * @return true (success) | false (failure, i.e., pid is not in the linked list
 * or index out of range (index >= size()))
 */
bool set_task(unsigned int index, unsigned int pid);

/**
 * Removes a task_struct (given pid) in the linked list and returns it.
 *
 * Does not deallocate memory occupied by the task_struct.
 *
 * @param pid
 * @return task_struct* (success) | NULL (failure, i.e., pid is not in the
 * linked list)
 */
task_struct* remove_task(unsigned int pid);

/**
 * If the task_struct with the given pid exists in the linked list, return it.
 * Else, return NULL.
 *
 * Does not deallocate memory occupied by the task_struct.
 *
 * @param pid
 * @return task_struct* (success) | NULL (failure, i.e., pid is not in the
 * linked list)
 */
task_struct* exists(unsigned int pid);

/**
 * Get the task_struct at the specified index and return it, if it exists. Else,
 * return NULL
 *
 * Does not deallocate memory occupied by the task_struct.
 *
 * @param index
 * @return task_struct* (success) | NULL (failure, i.e., index out of range
 * (index >= size()))
 */
task_struct* get_task(unsigned int index);

/**
 * Given two pids, swap the position of the task_structs with those pids.
 *
 * This can be accomplished simply by swapping the data fields (pid, priority,
 * remaining_cycles) of the two task_structs.
 *
 * @param pid_1
 * @param pid_2
 * @return true (success) | false (failure, i.e., pid_1 and/or pid_2 are not in
 * the linked list or pid_1 == pid_2)
 */
bool swap(unsigned int pid_1, unsigned int pid_2);

/**
 * Perform the min heapify algorithm on the linked list (converting it to a
 * priority queue), for use in priority-based scheduling
 *
 * See Heaps.pdf in this repo, which provides pseudocode. The pseudocode
 * is for a max heap, but the code for a min heap is very similar.
 *
 * The position of a task in the priority queue depends on its priority and
 * remaining_cycles. Specifically, use the float value priority /
 * remaining_cycles.
 *
 * `priority` is an `unsigned int` and `remaining_cycles` is an
 * `unsigned int`, so you have to cast both to `float` when dividing.
 * See code for print_tasks()
 *
 * Use the compare_floats function we provide to compare floats.
 * Do not use == with floats.
 *
 * For example, if Task 1 has priority 1 and remaining_cycles 5 (1/5 = 0.2)
 * and Task 2 has priority 5 and remaining_cycles 100 (5/100 = 0.05),
 * then Task 2 should be before Task 1 in the queue since 0.05 < 0.2.
 *
 * If this ratio is the same for two tasks, then the task with lower
 * `priority` should come first.
 *
 * If the `priority` is also the same, then
 * the relative ordering of the two tasks should remain the same. For example,
 * if comparing two child nodes, the left one would go first, and if comparing
 * a child and parent, then the parent would go first. This case will likely
 * already be taken care of, depending on your implementation, because the min
 * heapify algorithm is stable
 * (https://www.geeksforgeeks.org/stable-and-unstable-sorting-algorithms/).
 *
 * @return void
 */
void min_heapify();

/**
 * Print tasks
 *
 * @return void
 */
void print_tasks();

/**
 * Compare two floats
 *
 * See https://www.geeksforgeeks.org/comparison-float-value-c/
 *
 * @param a
 * @param b
 * @return 0 (|a - b| < epsilon) | 1 (a < b) | -1 (a > b)
 */
int compare_floats(float a, float b);

extern task_struct* head;
extern task_struct* tail;

#endif
