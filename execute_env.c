#include "simple.h"

extern char **environ;

void execute_env()
{
    char **env = environ;
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}
