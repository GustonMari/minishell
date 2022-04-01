/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:52:01 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 14:57:11 by ndormoy          ###   ########.fr       */
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

char	*add_join_export(char *str)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			new_str = ft_strdup(str);
			if (!new_str)
				return (NULL);
			return (new_str);
		}
		if (str[i + 1] && str[i] == '+' && str[i + 1] == '=')
		{
			new_str = remove_char_if(str, '+', '=');
			if (!new_str)
				return (NULL);
			return (new_str);
		}
		i++;
	}
	return (new_str);
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
			return (NULL);
		i++;
	}
	new_env[i] = add_join_export(str);
	new_env[i + 1] = NULL;
	ft_free_tab_2d(env);
	return (new_env);
}

char	**ft_export_change(char **env, char *str, char *name)
{
	char	*val;

	val = find_val_in_line(str);
	fprintf(stderr, "ici val = %s\n", val);
	fprintf(stderr, "str = %s\n", str);
	ft_change_env_val_export(env, name, val, str);
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
		&& ((!is_var_in_env_export(env, name, ft_strlen(name))) == 0))
		env = ft_export_add(env, str);
	else
		env = ft_export_change(env, str, name);
	free(ret);
	if (name)
		free(name);
	return (env);
}
