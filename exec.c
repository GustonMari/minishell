/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:00:48 by gmary             #+#    #+#             */
/*   Updated: 2022/02/17 17:53:36 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "function.h"

char	*find_path_cmd(char **env, char *cmd)
{
	int		i;
	char	*path;
	char	*new_cmd;
	char	**all_cmd_path;

	new_cmd = ft_strjoin("/", cmd);
	if (!new_cmd)
		return (NULL);
	all_cmd_path = ft_split(find_val_in_tab(env, "PATH"), ':');
	if (!all_cmd_path)
		return (NULL);
	i = 0;
	while (all_cmd_path[i++])
	{
		path = ft_strjoin(all_cmd_path[i], new_cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(new_cmd);
			ft_free_tab_2d(all_cmd_path);
			return (path);
		}
		free(path);
	}
	free(new_cmd);
	ft_free_tab_2d(all_cmd_path);
	return (NULL);
}

int ft_exec_cmd()
{
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*path;
	char **test = malloc (2 * sizeof(char *));
	test[0] = "ls";
	test[1] = NULL;
	path = find_path_cmd(env, "ls");
	printf("path = \"%s\"\n", path);
	if(execve(path, test, env) < 0)
		perror("execve");
	return (0);
}