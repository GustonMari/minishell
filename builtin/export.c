/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:52:01 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/28 16:12:52 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_export_no_arg(char **env)
{
	char	**env_sorted;

	env_sorted = bubble_sort_tab_2d(ft_strdup_2d(env));
	if (!env_sorted)
		return ;
	ft_print_export_no_arg(env_sorted);
	ft_free_tab_2d(env_sorted);
}

char	**ft_export_add(char **env, char *str)
{
	char	**new_env;
	int		line;
	int		i;

	i = 0;
	line = ft_count_line(env);
	new_env = malloc(sizeof(char *) * (line + 2));
	if (!new_env)
		return (NULL);
	while (i < line)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			//clear le tab JUSQUAU i
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	ft_free_tab_2d(env);
	return (new_env);
}

char	**ft_export_change(char **env, char *str, char *name)
{
	char	*val;

	val = find_val_in_line(str);
	ft_change_env_val_export(env, name, val);
	free(name);
	free(val);
	return (env);
}

char	**ft_export(char **env, char *str)
{
	char	*name;
	char	*ret;

	if (ft_check_export(str))
		return (env);
	name = find_name_val(str);
	if (is_var_in_env_export_2(env, str, ft_strlen(str)) == 0)
	{
		free(name);
		return (env);
	}
	ret = find_val_in_tab(env, name);
	if (ret == NULL
		&& !is_var_in_env_export(env, name, ft_strlen(name)) == 0)
		env = ft_export_add(env, str);
	else
		env = ft_export_change(env, str, name);
	free(ret);
	//A VOIR SI CA FOUT PAS LA MERDE
	free(name);
	return (env);
}

char	**manage_export(char **env, char **full_cmd)
{
	int	i;

	i = 1;
	g_status = 0;
	if (ft_count_line(full_cmd) == 1)
	{
		ft_export_no_arg(env);
		return (env);
	}
	while (full_cmd[i])
	{
		env = ft_export(env, full_cmd[i]);
		i++;
	}
	return (env);
}
/* int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	**env;

	env = ft_create_env(envp);
	ft_export_no_arg(env);
	ft_free_tab_2d(env);
} */