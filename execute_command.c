#include "simple.h"

/**
 * execute_command - Executes the given command with arguments
 */
int execute_command(char *command, char **envp)
{
	/* Check if the command exists in the PATH */
	char *path = getenv("PATH");
	char *path_token = strtok(path, ":");
	char executable_path[MAX_COMMAND_LENGTH];

	while (path_token != NULL)
	{
		snprintf(executable_path, sizeof(executable_path), "%s/%s", path_token, command);

		if (access(executable_path, X_OK) == 0)
		{
			/* Command exists, execute it */
			return execve(executable_path, (char *const *)&command, envp);
		}

		path_token = strtok(NULL, ":");
	}

	/* Command not found in PATH */
	fprintf(stderr, "Command not found: %s\n", command);
	return -1;
}
