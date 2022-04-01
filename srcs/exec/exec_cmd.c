/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:48:11 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 15:48:14 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_exec_cmd_bis_3(t_to_clean *clean, t_command *all, char *path)
{
	if (ft_strcmp(all->cmd_to_exec[0], "") == TRUE)
	{
		//WARNING
		free(path);
		ft_putstr_fd(BRED "minishell: : command not found\n" CRESET, 2);
		g_status = 127;
		ft_clean_exit(clean);
		exit(g_status);
	}
}

char	*ft_exec_cmd_bis_2(t_to_clean *clean, t_command *all, char *tmp)
{
	char	*path;

	path = chose_ath_cmd(all->cmd_to_exec[0], tmp);
	if (!path)
	{
		if (ft_strncmp((all->cmd_to_exec[0]), "./", 2) == TRUE)
		{
			redirection_error(ft_strdup(all->cmd_to_exec[0]));
			g_status = errno;
		}
		else
		{
			ft_print_error(1,
				all->cmd_to_exec[0], ": command not found", NULL);
			g_status = 127;
		}
		//WARNING
		if (tmp)
			free(tmp);
		ft_clean_exit(clean);
		exit(g_status);
	}
	return (path);
}

char	*ft_exec_cmd_bis(char **env
	, t_to_clean *clean, t_command *all, int *out)
{
	char	*tmp;

	tmp = NULL;
	if (*out != -1)
		close(*out);
	if (ft_strcmp(all->cmd_to_exec[0], "exit") == 0)
	{
		ft_exit(all, clean);
		ft_clean_exit(clean);
		exit(g_status);
	}
	g_status = 0;
	tmp = find_val_in_tab(env, "PATH");
	if (!tmp)
	{
		ft_print_error(1, all->cmd_to_exec[0], ": command not found", NULL);
		g_status = 127;
		ft_clean_exit(clean);
		//WARNING
		free(tmp);
		exit(127);
	}
	return (tmp);
}

int	ft_exec_cmd(char **env, t_to_clean *clean, t_command *all, int out)
{
	char	*path;
	char	*tmp;
	int		pid;

	path = NULL;
	prio_exit(all);
	signal_manager2();
	pid = fork();
	if (pid == 0)
	{
		tmp = ft_exec_cmd_bis(env, clean, all, &out);
		path = ft_exec_cmd_bis_2(clean, all, tmp);
		ft_exec_cmd_bis_3(clean, all, path);
		if (execve(path, all->cmd_to_exec, env) < 0)
		{
			ft_print_error(1, all->cmd_to_exec[0], ": Is a directory", NULL);
			g_status = 126;
			free(path);
			ft_clean_exit(clean);
			exit(g_status);
		}
		free(path);
		return (0);
	}
	return (0);
}

/* int	ft_exec_cmd(char **env, t_to_clean *clean, t_command *all, int out)
{
	char	*path;
	char	*tmp;
	int		pid;

	prio_exit(all);
	signal_manager2();
	pid = fork();
	if (pid == 0)
	{
		if (out != -1)
			close(out);
		if (ft_strcmp(all->cmd_to_exec[0], "exit") == 0)
		{
			ft_exit(all, clean);
			ft_clean_exit(clean);
			exit(g_status);
		}
		g_status = 0;
		tmp = find_val_in_tab(env, "PATH");
		if (!tmp)
		{
			ft_print_error(1, all->cmd_to_exec[0], ": command not found", NULL);
			g_status = 127;
			ft_clean_exit(clean);
			exit(127);
		}
		path = chose_ath_cmd(all->cmd_to_exec[0], tmp);
		if (!path)
		{
			if (ft_strncmp((all->cmd_to_exec[0]), "./", 2) == TRUE)
			{
				redirection_error(ft_strdup(all->cmd_to_exec[0]));
				g_status = errno;
			}
			else
			{
				ft_print_error(1,
					all->cmd_to_exec[0], ": command not found", NULL);
				g_status = 127;
			}
			ft_clean_exit(clean);
			exit(g_status);
		}
		if (ft_strcmp(all->cmd_to_exec[0], "") == TRUE)
		{
			ft_putstr_fd(BRED "minishell: : command not found\n" CRESET, 2);
			g_status = 127;
			ft_clean_exit(clean);
			exit(g_status);
		}
		if (execve(path, all->cmd_to_exec, env) < 0)
		{
			ft_print_error(1, all->cmd_to_exec[0], ": Is a directory", NULL);
			g_status = 126;
			free(path);
			ft_clean_exit(clean);
			exit(g_status);
		}
		free(path);
		return (0);
	}
	return (0);
} */