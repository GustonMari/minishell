/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:13:13 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/06 16:58:18 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	fill_heredoc_file_exit(char **stop, char *name, t_to_clean *clean)
{
	ft_clean_exit(clean);
	ft_free_tab_2d(stop);
	free(name);
	ft_putstr_fd("Quit (core dumped)\n", 2);
	g_status = 0;
	exit(g_status);
}

int	fill_heredoc_file_bis_2(char **stop, char *line, int begin, int fd)
{
	begin = start_heredoc_one(stop, begin);
	if (begin == 1)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	if (line)
		free(line);
	return (begin);
}

int	fill_heredoc_file_bis(char **stop, char *line, int *i)
{
	if (stop[*i] && !ft_strcmp(line, stop[*i]))
	{
		if (stop[*i + 1] == NULL)
		{
			free(line);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

/*Cette fonction permet de remplir le fichier 
temporaire tout en respecant les regles de priorite du heredoc*/

void	fill_heredoc_file(char **stop, int is_expand
	, char *name, t_to_clean *clean)
{
	char	*line;
	int		fd;
	int		i;
	int		begin;

	begin = 0;
	i = 0;
	line = NULL;
	fd = create_heredoc_file(name);
	while (1)
	{
		line = readline("> ");
		if (!line)
			fill_heredoc_file_exit(stop, name, clean);
		if (fill_heredoc_file_bis(stop, line, &i) == FALSE)
			break ;
		if (is_expand == TRUE)
			line = expand_dollar(clean->env, line, clean);
		begin = fill_heredoc_file_bis_2(stop, line, begin, fd);
		begin = start_heredoc_more(stop, i);
	}
	ft_free_tab_2d(stop);
	close(fd);
}
