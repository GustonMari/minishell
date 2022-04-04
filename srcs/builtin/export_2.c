/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:50:23 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 11:21:07 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Va checker si on a un += dans str, si oui, on va joinvar et new_val
pour pouvoir faire un join dans le cas --> export lol+=salut par exemple*/

char	*join_export(char *var, char *new_val, char *str, int *change)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
		{
			var = ft_strjoin_free(var, new_val, 1);
			if (!var)
				return (NULL);
			*change = 1;
		}
		i++;
	}
	fprintf(stderr, "nouvellleeeeee var = %s\n", var);
	return (var);
}

char	*ft_rpl_val_var_env_export_bis(char *var, char *new_val)
{
	char	*ret;

	ret = ft_strjoin(var, "=");
	ret = ft_strjoin_free(ret, new_val, 1);
	return (ret);
}

char	*ft_rpl_val_var_env_export(char *var, char *new_val, char *str)
{
	int		i;
	char	*ret;
	int		change;

	change = 0;
	i = 0;
	if (is_equal_in_line(var) == 0)
	{
		var = join_export(var, new_val, str, &change);
		if (change == 0)
		{
			while (var[i] != '=')
			i++;
			var[i + 1] = '\0';
			ret = ft_strjoin(var, new_val);
		}
		else
			ret = ft_strdup(var);
	}
	else
		ret = ft_rpl_val_var_env_export_bis(var, new_val);
	free(var);
	return (ret);
}

/* char	*ft_rpl_val_var_env_export(char *var, char *new_val, char *str)
{
	int		i;
	char	*ret;
	int		change;

	change = 0;
	i = 0;
	if (is_equal_in_line(var) == 0)
	{
		var = join_export(var, new_val, str, &change);
		if (change == 0)
		{
			while (var[i] != '=')
			i++;
			var[i + 1] = '\0';
			ret = ft_strjoin(var, new_val);
		}
		else
			ret = ft_strdup(var);
	}
	else
	{
		ret = ft_strjoin(var, "=");
		ret = ft_strjoin_free(ret, new_val, 1);
	}
	free(var);
	return (ret);
} */

int	ft_change_env_val_export(char **env, char *var, char *new_val, char *str)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!is_var_in_line_unset(env[i], var, ft_strlen(var)))
		{
			env[i] = ft_rpl_val_var_env_export(env[i], new_val, str);
			return (0);
		}
		i++;
	}
	return (1);
}
