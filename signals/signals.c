#include "../includes/function.h"

void	exit_pipe_process(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core umped)\n", 2);
	}
}

void	signal_in_cmd(void)
{
	if (signal(SIGQUIT, &exit_pipe_process) == SIG_ERR)
		ft_putstr_fd("Signal Error\n", 2);
	if (signal(SIGINT, &exit_pipe_process) == SIG_ERR)
		ft_putstr_fd("Signal Error\n", 2);	
}