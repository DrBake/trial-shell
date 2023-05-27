#include "simple.h"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], char *envp[])
{
	char command[MAX_COMMAND_LENGTH];
	char prompt[] = "simple_shell$ ";
	int should_run = 1;

	while (should_run)
	{
		pid_t pid;
		int status;

		printf("%s", prompt);
		fflush(stdout);

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			/* End of file (Ctrl+D) or error occurred */
			break;
		}

		/* Remove the newline character from the command */
		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			/* Handle the exit command */
			execute_exit();
		}else if (strcmp(command, "env") == 0)
		{
			/* Handle the env command */
			execute_env();
		}

		pid = fork();

		if (pid < 0)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			int result = execute_command(command, envp);

			if (result == -1)
				exit(EXIT_FAILURE);

			exit(EXIT_SUCCESS);
		}
		else
		{
			/* Parent process */
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
			{
				int exit_status = WEXITSTATUS(status);
				printf("Child process exited with status %d\n", exit_status);
			}
			else if (WIFSIGNALED(status))
			{
				int term_signal = WTERMSIG(status);
				printf("Child process terminated by signal %d\n", term_signal);
				fflush(stdout);
			}
		}
	}

	printf("\nExiting the shell...\n");
	return (0);
}
