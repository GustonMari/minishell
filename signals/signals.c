#include "../includes/function.h"

void	exit_pipe_process(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	signal_in_cmd(void)
{
	if (signal(SIGQUIT, &exit_pipe_process) == SIG_ERR)
		ft_putstr_fd("Signal Error\n", 2);
	if (signal(SIGINT, &exit_pipe_process) == SIG_ERR)
		ft_putstr_fd("Signal Error\n", 2);	
}


void	signal_cmd(int sig)
{
	if (sig == SIGINT)
	{
		//write(1, "\n\e[1;91m- SIGINT -\n", 20);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
		g_status = 130;
		exit(g_status);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	signal_manager2(void)
{
	if (signal(SIGINT, &signal_cmd) == SIG_ERR)
		fprintf(stderr, "Error: %s\n", strerror(errno));
	if (signal(SIGQUIT, &signal_cmd) == SIG_ERR)
		fprintf(stderr, "Error: %s\n", strerror(errno));
}