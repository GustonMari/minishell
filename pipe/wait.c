#include "../includes/function.h"

void	exit_pipe_process(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	/* printf("exited NTM\n"); */
}

int	wait_pipe(int nb_cmd)
{
    int		status;
    int		i;

    i = 0;
    while (i < nb_cmd)
	{
		if (signal(SIGINT, &exit_pipe_process) == SIG_ERR)
			return (fprintf(stderr, "Error: %s\n", strerror(errno)));
		wait(&status);
		i++;
	}
	return (0);
}