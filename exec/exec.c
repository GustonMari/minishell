/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:00:48 by gmary             #+#    #+#             */
/*   Updated: 2022/03/23 16:58:16 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Trouve si la cmd en parametre est une cmd
avec un chemin absolut*/

char	*find_absolute_path_cmd(char *cmd, char *tmp)
{
	int		i;
	char	**all_cmd_path;

	all_cmd_path = ft_split(tmp, ':');
	if (!all_cmd_path)
		return (NULL);
	i = -1;
	while (all_cmd_path[++i])
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			ft_free_tab_2d(all_cmd_path);
			return (ft_strdup(cmd));
		}
	}
	ft_free_tab_2d(all_cmd_path);
	return (NULL);
}

/*Trouve si la cmd en parametre est une cmd
avec un chemin relatif*/

char	*find_path_cmd(char *cmd_to_join, char *tmp)
{
	int		i;
	char	*path;
	char	**all_cmd_path;
	char	*cmd;

	cmd = ft_strjoin("/", cmd_to_join);
	if (!cmd)
		return (NULL);
	all_cmd_path = ft_split(tmp, ':');
	if (!all_cmd_path)
		return (NULL);
	i = -1;
	while (all_cmd_path[++i])
	{
		path = ft_strjoin(all_cmd_path[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(cmd);
			ft_free_tab_2d(all_cmd_path);
			return (path);
		}
		free(path);
	}
	free(cmd);
	ft_free_tab_2d(all_cmd_path);
	return (NULL);
}

/*Va regarder si la commande est une commande
avec un chemin absolut ou relatif, renvoi le path
si il y avait un chemin absolut ou relatif, renvoie
NULL si il n'y avait aucun des deux*/

char	*chose_ath_cmd(char *cmd, char *tmp)
{
	char	*path;

	path = find_path_cmd(cmd, tmp);
	if (path == NULL)
		path = find_absolute_path_cmd(cmd, tmp);
	free(tmp);
	return (path);
}

int	ft_exec_cmd(char **env, char **full_cmd, int out)
{
	char	*path;
	char	*tmp;
	int		pid;
	
	
	pid = fork();
	//signal_manager2();
	if (pid == 0)
	{
		if (out != -1)
			close(out);
		g_status = 0;
		tmp = find_val_in_tab(env, "PATH");
		if (!tmp)
			return (-1);
		path = chose_ath_cmd(full_cmd[0], tmp);
		if (!path)
		{
			ft_print_error(1, full_cmd[0], ": command not found", NULL);
			g_status = 127;
			exit(127);
		}
		if (execve(path, full_cmd, env) < 0)
		{
			perror("execve");
			g_status = errno;
			exit(1);
		}
		free(path);
		return (0);
	}
	return (0);
}

char	**ft_exec_builtin(char **env, char **full_cmd, int builtin)
{
	if (builtin == FT_CD)
		ft_cd(full_cmd, env);
	if (builtin == FT_UNSET)
	{
		env = ft_unset(env, full_cmd);
		if (!env)
			return (NULL);
	}
	if (builtin == FT_EXPORT)
		env = manage_export(env, full_cmd);
	if (builtin == FT_PWD)
		ft_pwd();
	if (builtin == FT_ENV)
		ft_print_env(env);
	if (builtin == FT_ECHO)
		ft_echo(full_cmd);
	return (env);
}

int	ft_exec(char **env, char **full_cmd, int out)
{
	int	builtin;

	builtin = is_builtin(full_cmd[0]);
	if (builtin)
	{
		env = ft_exec_builtin(env, full_cmd, builtin);
		//exit(0);
	}
	else
		ft_exec_cmd(env, full_cmd, out);
	return (0);
}

/* int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char **test = malloc (3 * sizeof(char *));
	test[0] = "ls";
	test[1] = "-la";
	test[2] = NULL;

	ft_exec_cmd(envint	check_t_cmd(char **env, t_command *all)
{
	t_command *tmp;

	tmp = all;
	while (tmp)
	{
		if (is_valid_cmd(env, tmp->cmd_to_exec) == -1)
		{
			ft_putstr_fd(BRED tmp->cmd_to_exec[0] CRESET, 2);
			perror(BRED ": command not found" CRESET);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}*/