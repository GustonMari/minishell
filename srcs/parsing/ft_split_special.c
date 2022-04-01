
#include "../includes/function.h"

int	ft_count_word(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
		{
			i += find_next_quote(&str[i]);
			count++;
		}
		else if (str[i] == D_QUOTE)
		{
			i += find_next_quote(&str[i]);
			count++;
		}
		else if (str[i])
		{
			count++;
			while (str[i] && (str[i] != QUOTE && str[i] != D_QUOTE))
				i++;
		}
	}
	return (count);
}

/*
	Prends la chaine de char str qui a ete lexe et la split en un tab,
	on garde les quote & d_quote ainsi que les espaces,
	on passera le retour dans le trimeur
*/

char	**ft_split_special(char *str)
{
	int		i;
	int		j;
	int		nb_word;
	int		len_word;
	char	**tab;

	j = 0;
	i = -1;
	nb_word = (ft_count_word(str));
	tab = malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	while (++i < nb_word)
	{
		len_word = find_next_quote(&str[j]);
		tab[i] = ft_substr(&str[j], 0, len_word);
		if (!tab[i])
			return (ft_free_tab_2d(tab));
		j += len_word;
	}
	tab[i] = NULL;
	return (tab);
}

/* Il faudra free str qui sera alloué*/

/* int main()
{
	char	*str = " \"ca\" | \'va\' toi\"$USER\" > \"oui\'ii\"";
	char	**strs;

	strs = ft_split_special(str);
	print_tab_2d(strs);
	ft_free_tab_2d(strs);

	return (0);
} */