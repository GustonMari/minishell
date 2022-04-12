/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bis_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:30:21 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/12 13:40:27 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	launch_heredoc_bis_2(char **stop, char *name,
	int is_expand, t_to_clean *clean)
{
	fill_heredoc_file(stop, is_expand, name, clean);
	ft_clean_exit(clean);
	free(name);
	exit(g_status);
}

char	**launch_heredoc_bis(t_command **all_cmd, char **stop, int *is_expand)
{
	signal_heredoc();
	stop = create_tab_stop(*all_cmd);
	if (!stop)
		return (NULL);
	if (is_expand_heredoc(stop) == TRUE)
		*is_expand = TRUE;
	else
		*is_expand = FALSE;
	stop = trim_quote_stop(stop);
	if (!stop)
		return (NULL);
	return (stop);
}

int	launch_heredoc(t_command **all_cmd, char *name, t_to_clean *clean)
{
	char	**stop;
	int		is_expand;
	pid_t	pid;

	stop = NULL;
	is_expand = -1;
	if (signal_launch_heredoc() == FALSE)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		stop = launch_heredoc_bis(all_cmd, stop, &is_expand);
		if (!stop)
			return (-1);
		launch_heredoc_bis_2(stop, name, is_expand, clean);
	}
	else
		wait_heredoc();
	if (g_status == 255)
	{
		g_status = 130;
		return (-2);
	}
	return (0);
}

int	replace_heredoc_bis(t_command **all_cmd, char *name)
{
	char	**name_2d;

	if ((*all_cmd) && (*all_cmd)->next)
	{
		ft_free_tab_2d((*all_cmd)->next->cmd_to_exec);
		(*all_cmd)->next->type = WORD;
		(*all_cmd)->next->to_del = 1;
		name_2d = ft_calloc(sizeof(char *), 2);
		if (!name_2d)
			return (-1);
		name_2d[0] = name;
		name_2d[1] = NULL;
		(*all_cmd)->next->cmd_to_exec = name_2d;
	}
	else
		return (-1);
	return (0);
}

/*Permet de remplacer << par < et le word suivant par
le nom du heredoc qui etait dispo*/

int	replace_heredoc(t_command **all_cmd, char *name)
{
	char	**d_chv;

	ft_free_tab_2d((*all_cmd)->cmd_to_exec);
	(*all_cmd)->type = CHV_L;
	d_chv = ft_calloc(sizeof(char *), 2);
	if (!d_chv)
		return (-1);
	d_chv[0] = ft_strdup("<");
	if (!d_chv[0])
	{
		free(d_chv);
		return (-1);
	}
	d_chv[1] = NULL;
	(*all_cmd)->cmd_to_exec = d_chv;
	if (replace_heredoc_bis(all_cmd, name) == -1)
		return (-1);
	return (0);
}

/* int	replace_heredoc(t_command **all_cmd, char *name)
{
	char	**d_chv;
	char	**name_2d;

	ft_free_tab_2d((*all_cmd)->cmd_to_exec);
	(*all_cmd)->type = CHV_L;
	d_chv = ft_calloc(sizeof(char *), 2);
	if (!d_chv)
		return (-1);
	d_chv[0] = ft_strdup("<");
	if (!d_chv[0])
	{
		free(d_chv);
		return (-1);
	}
	d_chv[1] = NULL;
	(*all_cmd)->cmd_to_exec = d_chv;
	if ((*all_cmd) && (*all_cmd)->next)
	{
		ft_free_tab_2d((*all_cmd)->next->cmd_to_exec);
		(*all_cmd)->next->type = WORD;
		(*all_cmd)->next->to_del = 1;
		name_2d = ft_calloc(sizeof(char *), 2);
		if (!name_2d)
			return (-1);
		name_2d[0] = name;
		name_2d[1] = NULL;
		(*all_cmd)->next->cmd_to_exec = name_2d;
	}
	else
		return (-1);
	return (0);
} */