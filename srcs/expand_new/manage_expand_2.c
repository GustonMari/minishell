/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:58:56 by gmary             #+#    #+#             */
/*   Updated: 2022/03/31 17:31:16 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	nb_back_slash(char *str)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
			nb ++;
		i++;
	}
	return (nb);
}

int	nb_dollar(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nb++;
		i++;
	}
	return (nb);
}

char	*allocate_echapment(char *new, char *str, t_to_clean *clean)
{
	new = malloc(sizeof(char) * (ft_strlen(str) + nb_dollar(str) + 1));
	if (!new)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (new);
}

char	*add_echapment(char *str, t_to_clean *clean)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = NULL;
	new = allocate_echapment(new, str, clean);
	while (str[i])
	{
		if (str[i] == '$')
		{
			new[j] = BACK_SLASH;
			j++;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

/*Supprime tous les backslash devant un dollar dans la string*/

char	*del_back_slash(char *str, t_to_clean *clean)
{
	int		i;
	int		j;
	int		nb;
	char	*block;

	i = 0;
	j = 0;
	nb = 0;
	nb = nb_back_slash(str);
	block = malloc(sizeof(char) * (ft_strlen(str) + 1 - nb));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
			i++;
		block[j] = str[i];
		i++;
		j++;
	}
	block[j] = '\0';
	free(str);
	return (block);
}

/*Expand un maillon */

char	*expand_node(char **env, char *str, t_to_clean *clean)
{
	int		i;
	char	*block;
	char	*expanded;

	block = NULL;
	expanded = ft_strdup("");
	if (!expanded)
		return (ft_clean_error_malloc(clean));
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			block = trim_quote(block, &i, clean);
			block = add_echapment(block, clean);
		}
		else if (str[i] == D_QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			block = trim_quote(block, &i, clean);
			block = expand_dollar(block, clean);
		}
		else if (str[i] == '$')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			if (str[i + 1] != '\0')
				block = expand_single_dollar(env, block, clean);
			block = del_back_slash(block, clean);
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			i++;
			block = cpy_block_special(&str[i], find_next_block(&str[i]), clean);
			i += find_next_block(&str[i]);
		}
		else
		{
			block = cpy_block(&str[i], find_next_block(&str[i]), clean);
			i += find_next_block(&str[i]);
		}
		expanded = ft_strjoin_free(expanded, block, 1);
		if (!expanded)
		{
			free(str);
			free(block);
			return (ft_clean_error_malloc(clean));
		}
		free(block);
	}
	free(str);
	return (expanded);
}
