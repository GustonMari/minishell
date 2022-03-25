#include "../includes/function.h"

/*Permet de creer le fichier .heredoc ou que l'on va
utiliser pour sotcker ce qu'on met dans heredoc*/

int	create_heredoc_file(char *name)
{
	int	file;

	file = open(name, O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (file < 0)
		return (-1);
	return (file);
}

/*Permet de savoir quand debuter ou pas l'ecriture dans le fichier
heredoc*/

int	start_heredoc_one(char **stop, int begin)
{
	int	start;
	start = 0;
	
	if (begin == 1)
		return (1);
	start = ft_count_line(stop);
	if (start == 1)
		return (1);
	return (0);
}

int	start_heredoc_more(char **stop, int i)
{
	int	start;
	
	start = ft_count_line(stop);
/* 	if (start == 1)
		return (1); */
	if (i == start - 1)
		return (1);
	return (0);
}

void	exit_heredoc(int sig)
{
	//printf("salut\n");

	(void)sig;
		//printf("\n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
		//rl_redisplay();
		g_status = 130;
	// changer valeur de lexit
	//exit(0);
	/* if (sig == SIGINT)
		return (0);
	return (1); */
}


void	manage_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		//rl_redisplay();g_status = 130;
		g_status = 130;
		write(1, "\n", 1);
		exit(255);
	}
}

int	signal_heredoc(void)
{
	if (signal(SIGINT, &manage_heredoc_signal) == SIG_ERR)
		return (1);
	//fprintf(stderr, "dhjskfkjshdkfjhkdfjhkdjhfkdhfkjhfkdjhfk  %d\n", g_status);

	//if (signal(SIGINT, &manage_heredoc_signal) == SIG_ERR)
	//	return (1);
		//fprintf(stderr, "Error: %s\n", strerror(errno));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	// if (signal(SIGHUP, &manage_heredoc_signal) == SIG_ERR)
	// {
	// 	fprintf(stderr, "saluttuututut\n");
	// 	return (1);
	// }

		//fprintf(stderr, "Error: %s\n", strerror(errno));
	//int		status;
	return (0);
}

/* int	signal_heredoc(char **stop, char *line)
{
	//int		status;
	(void)stop;
	// gerer ctrl backslash et status aussi !!!!!!
	printf("salut\n");
	if (signal(SIGINT, &exit_heredoc) == SIG_ERR)
	{
		printf("SIGINT");
		return (1);
	}
	if (!line)
	{
		//clear history si il y en avait un
		//write(2, "\n\e[0;35mctrl+D used\n", 21);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
} */