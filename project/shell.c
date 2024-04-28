// PID: 730677144
// I pledge the COMP 211 honor code.

// All necessary libraries are included in shell.h
#include "shell.h"

void alloc_mem_for_argv(command_t* p_cmd) {
    p_cmd->argv = (char**)malloc((p_cmd->argc + 1) * sizeof(char*));
    for (int i = 0; i < p_cmd->argc; i++) {
        p_cmd->argv[i] = (char*)malloc(MAX_ARG_LEN * sizeof(char));
    }

    p_cmd->argv[p_cmd->argc] = NULL;
}

void cleanup(command_t* p_cmd) {
    for (int i = 0; i < p_cmd->argc; i++) {
        free(p_cmd->argv[i]);
        p_cmd->argv[i] = NULL;
    }

    free(p_cmd->argv);
    p_cmd->argv = NULL;
}

void parse(char* line, command_t* p_cmd) {
    char* line_copy = strdup(line);
    char* token = strtok(line_copy, " ");
    p_cmd->argc = 0;

    while (token != NULL) {
        p_cmd->argc++;
        token = strtok(NULL, " ");
    }

    free(line_copy);

    alloc_mem_for_argv(p_cmd);

    line_copy = strdup(line);
    token = strtok(line_copy, " ");

    for (int i = 0; i < p_cmd->argc; i++) {
        strcpy(p_cmd->argv[i], token);
        token = strtok(NULL, " ");
    }

    free(line_copy);
}

bool find_full_path(command_t* p_cmd) {
    char* path = strdup(getenv("PATH"));
    char* token = strtok(path, ":");

    while (token != NULL) {
        char* full_path = (char*)malloc(MAX_ARG_LEN * sizeof(char));
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, p_cmd->argv[0]);

        if (access(full_path, F_OK) == 0) {
            strcpy(p_cmd->argv[0], full_path);
            free(path);
            free(full_path);
            return true;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path);

    return false;
}

int execute(command_t* p_cmd) {
    if (is_builtin(p_cmd)) {
        return do_builtin(p_cmd);
    }

    if (!find_full_path(p_cmd)) {
        printf("Command %s not found!\n", p_cmd->argv[0]);
        return ERROR;
    }

    // start fork
    pid_t pid = fork();

    if (pid < 0) {
        return ERROR;
    } else if (pid == 0) {
        // child process
        execv(p_cmd->argv[0], p_cmd->argv);
        exit(EXIT_FAILURE);
    } else {
        // parent process
        int status;
        waitpid(pid, &status, 0);
    }

    return SUCCESS;
}

bool is_builtin(command_t* p_cmd) {
    // Do not modify
    char* executable = p_cmd->argv[0];
    if (strcmp(executable, "cd") == 0 || strcmp(executable, "exit") == 0) {
        return true;
    }
    return false;
}

int do_builtin(command_t* p_cmd) {
    // Do not modify
    if (strcmp(p_cmd->argv[0], "exit") == 0) {
        exit(SUCCESS);
    }

    // cd
    if (p_cmd->argc == 1) {  // cd with no arguments
        return chdir(getenv("HOME"));
    } else if (p_cmd->argc == 2) {  // cd with 1 arg
        return chdir(p_cmd->argv[1]);
    } else {
        fprintf(stderr, "cd: Too many arguments\n");
        return ERROR;
    }
}
