// PID: 730677144
// I pledge the COMP 211 honor code.

#include "task.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Pointers to the head and tail of the linked list to be used in the functions

task_struct* head = NULL;
task_struct* tail = NULL;

void clear() {
    // DO NOT MODIFY
    while (head != NULL) {
        task_struct* tmp = head->next;
        free(head);
        head = tmp;
    }
    head = NULL;
    tail = NULL;
}

unsigned int size() {
    // DO NOT MODIFY
    if (head == NULL)
        return 0;
    task_struct* tmp = head;
    unsigned int sz = 1;
    while ((tmp = tmp->next) != NULL)
        sz++;
    return sz;
}

bool append_task(unsigned int pid, unsigned int priority, unsigned int cycles) {
    // DO NOT MODIFY
    if (exists(pid) != NULL)
        return false;

    task_struct* new = malloc(sizeof(task_struct));
    new->pid = pid;
    new->priority = priority;
    new->remaining_cycles = cycles;
    new->next = NULL;

    if (head == NULL) {
        head = new;
        tail = new;
    } else {
        tail->next = new;
        tail = new;
    }
    return true;
}

bool insert_task(unsigned int index,
                 unsigned int pid,
                 unsigned int priority,
                 unsigned int cycles) {
    // DO NOT MODIFY
    if (exists(pid) != NULL || index > size())
        return false;

    task_struct* new = malloc(sizeof(task_struct));
    new->pid = pid;
    new->priority = priority;
    new->remaining_cycles = cycles;

    if (index == 0) {
        task_struct* tmp = head;
        head = new;
        new->next = tmp;
    } else {
        if (index == size())
            tail = new;
        task_struct* tmp = get_task(index - 1);

        new->next = tmp->next;
        tmp->next = new;
    }
    return true;
}

bool set_task(unsigned int index, unsigned int pid) {
    // DO NOT MODIFY
    if (exists(pid) == NULL || index >= size())
        return false;

    task_struct* tmp = exists(pid);

    if (get_task(index)->pid == tmp->pid)
        return false;

    remove_task(pid);
    insert_task(index, tmp->pid, tmp->priority, tmp->remaining_cycles);

    return true;
}

task_struct* remove_task(unsigned int pid) {
    // DO NOT MODIFY
    if (size() == 0)
        return NULL;
    int sz = size();
    task_struct* tmp = head;
    if (pid == head->pid) {
        head = head->next;
        return tmp;
    }
    for (int i = 0; i < sz - 1; i++) {
        if (tmp->next->pid == pid) {
            if (tmp->next->pid == tail->pid)
                tail = tmp;
            task_struct* rem = tmp->next;
            tmp->next = rem->next;
            return rem;
        }
        tmp = tmp->next;
    }
    return NULL;
}

task_struct* exists(unsigned int pid) {
    // DO NOT MODIFY
    int sz = size();
    task_struct* tmp = head;
    for (int i = 0; i < sz; i++) {
        if (tmp->pid == pid) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

task_struct* get_task(unsigned int index) {
    // DO NOT MODIFY
    if (index >= size())
        return NULL;
    task_struct* tmp = head;
    while (index > 0) {
        tmp = tmp->next;
        index--;
    }
    return tmp;
}

bool swap(unsigned int pid_1, unsigned int pid_2) {
    // DO NOT MODIFY
    task_struct* first = exists(pid_1);
    task_struct* second = exists(pid_2);
    if (first == NULL || second == NULL || pid_1 == pid_2 || size() == 1)
        return false;
    task_struct* tmp = malloc(sizeof(task_struct));

    tmp->priority = first->priority;
    tmp->pid = first->pid;
    tmp->remaining_cycles = first->remaining_cycles;

    first->priority = second->priority;
    first->pid = second->pid;
    first->remaining_cycles = second->remaining_cycles;

    second->priority = tmp->priority;
    second->pid = tmp->pid;
    second->remaining_cycles = tmp->remaining_cycles;

    free(tmp);
    return true;
}

void heapify(int i) {
    bool done = false;
    int k = i;

    while (!done && (2 * k + 1) < size()) {
        int j = 2 * k + 1;

        if (j + 1 < size()) {
            // two children

            task_struct* left = get_task(j);
            task_struct* right = get_task(j + 1);

            float left_ratio =
                (float)left->priority / (float)left->remaining_cycles;
            float right_ratio =
                (float)right->priority / (float)right->remaining_cycles;

            if (right_ratio < left_ratio) {
                j++;
            }
        }

        task_struct* curr = get_task(k);
        task_struct* next = get_task(j);

        float curr_ratio =
            (float)curr->priority / (float)curr->remaining_cycles;
        float next_ratio =
            (float)next->priority / (float)next->remaining_cycles;

        if (curr_ratio > next_ratio ||
            (curr_ratio == next_ratio && curr->priority > next->priority)) {
            swap(curr->pid, next->pid);
            k = j;
        } else {
            done = true;
        }
    }
}

void min_heapify() {
    for (int i = floor((size() - 2) / 2); i >= 0; i--) {
        heapify(i);
    }
}

void print_tasks() {
    // DO NOT MODIFY
    task_struct* p_task = head;

    if (p_task == NULL) {
        printf("[ empty ]\n");
    } else {
        printf("(%d) [", size());

        while (p_task != NULL) {
            printf(" %d:%d:%d:%.2f", p_task->pid, p_task->priority,
                   p_task->remaining_cycles,
                   (float)p_task->priority / (float)p_task->remaining_cycles);
            p_task = p_task->next;
        }

        printf(" ]\n");
    }
}

int compare_floats(float a, float b) {
    // DO NOT MODIFY
    return fabs(a - b) < EPSILON ? 0 : a < b ? 1 : -1;
}
