/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:05:45 by gmary             #+#    #+#             */
/*   Updated: 2022/03/01 09:18:01 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	word;
	int	count;

	count = 0;
	word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			word = 0;
		if (word == 0)
		{
			if (s[i] != c && word == 0)
			{
				word = 1;
				count++;
			}
		}
		i++;
	}
	return (count);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i + 1);
}

static char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_cut(char const *s, char **split, char c, int i)
{
	int		j;
	int		l;

	j = -1;
	while (++j < ft_wordcount(s, c))
	{
		l = 0;
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c)
		{
			split[j] = malloc(sizeof(char) * ft_wordlen(&s[i], c));
			if (!split[j])
				return (free_tab(split));
			while (s[i] != c && s[i])
			{
				split[j][l] = s[i];
				i++;
				l++;
			}
			split[j][l] = '\0';
		}
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!split)
		return (NULL);
	return (ft_cut(s, split, c, i));
}
