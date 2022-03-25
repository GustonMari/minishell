#include "../includes/function.h"



int	wait_pipe(void)
{
	int		status;

	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)));
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)));
	return (0);
}

/* int	wait_pipe(void)
{
	int		status;

	while (waitpid(-1, &status, 0) != -1)
	{
		//if (signal(SIGINT, &exit_pipe_process) == SIG_ERR)
		//	return (fprintf(stderr, "Error: %s\n", strerror(errno)));
		//if (signal(SIGQUIT, &exit_pipe_process) == SIG_ERR)
		//	return (fprintf(stderr, "Error: %s\n", strerror(errno)));
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)));
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)));
	return (0);
} */
