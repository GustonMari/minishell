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
	if (i == start - 1)
		return (1);
	return (0);
}

void	exit_heredoc(int sig)
{
	(void)sig;
	g_status = 130;
}


void	manage_heredoc_signal(int sig)
{
	const char *tab[20] = {"clean_heredoc", NULL};

	if (sig == SIGINT)
	{
		g_status = 130;
		write(1, "\n", 1);
		execve("srcs/heredoc/clean_heredoc", (char **const)tab, NULL);
		exit(255);
	}
}

int	signal_heredoc(void)
{
	if (signal(SIGINT, &manage_heredoc_signal) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
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