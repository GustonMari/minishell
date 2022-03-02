/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:00:48 by gmary             #+#    #+#             */
/*   Updated: 2022/03/02 11:59:52 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/function.h"

char	*find_path_cmd(char *cmd, char *tmp)
{
	int		i;
	char	*path;
	char	**all_cmd_path;

	all_cmd_path = ft_split(tmp, ':');
	if (!all_cmd_path)
		return (NULL);
	free(tmp);
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

int	ft_exec_cmd(char **env, char **full_cmd)
{
	char	*new_cmd;
	char	*path;
	char	*tmp;

	tmp = find_val_in_tab(env, "PATH");
	if (!tmp)
		return (-1);
	new_cmd = ft_strjoin("/", full_cmd[0]);
	if (!new_cmd)
		return (-1);
	path = find_path_cmd(new_cmd, tmp);
	if (!path)
	{
		ft_print_error(0, full_cmd[0], ": command not found", NULL);
		exit(1);
	}
	if(execve(path, full_cmd, env) < 0)
		perror("execve");
	free(path);
	return (0);
}

int	ft_exec_builtin(char **env, char **full_cmd, int builtin)
{
	
}

int	ft_exec(char **env, char **full_cmd)
{
	int	builtin;

	builtin = is_builtin(full_cmd[0]);
	if (builtin)
	{
		ft_exec_builtin(env, full_cmd, builtin);
		return (0);
	}
	else
		ft_exec_cmd(env, full_cmd);
	return (0);
}

/* int	ft_exec_cmd(char **env, char **full_cmd)
{
	char	*new_cmd;
	char	*path;
	char	*tmp;
	int		status;

	tmp = find_val_in_tab(env, "PATH");
	if (!tmp)
		return (-1);
	new_cmd = ft_strjoin("/", full_cmd[0]);
	if (!new_cmd)
		return (-1);
	path = find_path_cmd(new_cmd, tmp);
	if (!path)
		return (-1);

	int	pid = fork();
	if (pid == 0)
	{
		if(execve(path, full_cmd, env) < 0)
			perror("execve");
		free(path);
	}else
		wait(&status);
	return (0);
} */


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