#include "../includes/function.h"



int	wait_pipe(void)
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
	return (0);
}

/* int	wait_pipe(int nb_cmd)
{
	int		status;
	int		i;

	i = 0;
	while (i < nb_cmd)
	{
		if (signal(SIGINT, &exit_pipe_process) == SIG_ERR)
			return (fprintf(stderr, "Error: %s\n", strerror(errno)));
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		i++;
	}
	return (0);
} */