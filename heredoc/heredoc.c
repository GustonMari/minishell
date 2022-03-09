#include "../includes/function.h"


/*Permet de creer le fichier .heredoc ou que l'on va
utiliser pour sotcker ce qu'on met dans heredoc*/

int	create_heredoc_file(void)
{
	int	file;

	file = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (file < 0)
		return (-1);
	return (file);
}

int	start_heredoc(char **stop, int i)
{
	int	start;
	
	start = ft_count_line(stop);
	if (start == 1)
		return (1);
	if (i == start - 1)
		return (1);
	return (0);
}

void	fill_heredoc_file(char **stop)
{
	char	*line;
	int		fd;
	int		i;
	int 	begin;

	begin = 0;
	i = 0;
	fd = create_heredoc_file();
	line = NULL;
	while (1)
	{
		line = readline("> ");
		//Gerer les signaux
		if (!ft_strcmp(line, stop[i]))
		{
			if (stop[i + 1] == NULL)
			{
				free(line);
				break ;
			}
			i++;
		}
		if (begin == 1)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		if (line)
			free(line);
		begin = start_heredoc(stop, i);
	}
}

int main()
{
	char *tab[] = {"mdr", "ca va", "yes", "pouet", NULL};
	fill_heredoc_file(tab);
	return (0);
}