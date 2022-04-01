/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:54:58 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 16:31:09 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Permet de creer le tableau a double dimension contenant les
limitor, chaque dimension en contient un.*/

char	**create_tab_stop(t_command *all_cmd)
{
	t_command	*tmp;
	char		**stop;
	int			i;

	i = 0;
	tmp = all_cmd;
	stop = NULL;
	stop = malloc(sizeof(char *) * (count_nb_D_CHV_L_between_pipe(tmp) + 1));
	if (!stop)
		return (NULL);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_CHV_L)
		{
			stop[i] = ft_strdup(tmp->next->cmd_to_exec[0]);
			if (!stop[i])
				return (NULL);
			i++;
		}
		tmp = tmp->next;
	}
	stop[i] = NULL;
	return (stop);
}

/*Trouve un nom de heredoc valide*/

char	*find_heredoc_name(void)
{
	static int	i = 0;
	char		*name;

	name = NULL;
	while (1)
	{
		name = ft_strjoin_free(".heredoc", ft_itoa(i), 2);
		if (!name)
			return (NULL);
		if (access(name, F_OK) < 0)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}

/*Fonction qui manage le heredoc*/

int	manage_heredoc(t_command **all_cmd, t_to_clean *clean)
{
	int			ret;
	t_command	*tmp;
	char		*name;

	ret = 0;
	tmp = *all_cmd;
	while (tmp)
	{
		if (tmp->type == D_CHV_L && tmp->next && tmp->next->type == WORD)
		{
			name = find_heredoc_name();
			if (!name)
				return (-1);
			ret = launch_heredoc(&tmp, name, clean);
			replace_heredoc(&tmp, name);
			if (ret < 0)
				return (ret);
			count_all_between_pipe(&tmp);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
