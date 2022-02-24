#include "../includes/function.h"

static int	ft_charisset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_cut(int begin, int end, char *trim, char *s1)
{
	int		i;

	i = 0;
	if (begin < end)
	{
		while (begin < end)
			trim[i++] = s1[begin++];
	}
	trim[i] = '\0';
	return (trim);
}


/*
	fonctionne presque comme un strtrim traditionnel 
	mais permet de garder UN SEUL espace avant ou apres le mots si il y en a
	ATTENTION SI ON ENVOIE UN SEUL ESPACE IL NE TRIM PAS 
*/

char	*ft_strtrim_space(char *s1, char *set)
{
	char	*trim;
	int		begin;
	int		end;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] && ft_charisset(s1[begin], set))
	{
		if (!ft_charisset(s1[begin + 1], set))
			break ;
		begin++;

	}
	while (s1[end - 1] && ft_charisset(s1[end - 1], set))
	{
		if (!ft_charisset(s1[end - 2], set))
			break ;
		end--;
	}
	if (end < begin)
		begin = end;
	trim = malloc(sizeof(char) * ((end - begin) + 1));
	if (!trim)
		return (NULL);
	return (ft_cut(begin, end, trim, s1));
}

/* int	main()
{
	char *str = "     ";

	printf("%s\n", ft_strtrim_space(str, " \t\n\v\f\r"));
	return (0);
} */