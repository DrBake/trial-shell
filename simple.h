#ifndef _SIMPLE_H
#define _SIMPLE_H

#define MAX_COMMAND 100
#define MAX_COMMAND_LENGTH 100
#define BF_SZ 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stddef.h>
#include <fcntl.h>
#include <signal.h>


int execute_command(char *command, char **envp);
void execute_exit(void);
void execute_env();

#endif
