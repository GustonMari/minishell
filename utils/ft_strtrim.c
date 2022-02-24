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

char	*ft_strtrim(char *s1, char *set)
{
	char	*trim;
	int		begin;
	int		end;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] && ft_charisset(s1[begin], set))
		begin++;
	while (s1[end - 1] && ft_charisset(s1[end - 1], set))
		end--;
	if (end < begin)
		begin = end;
	trim = malloc(sizeof(char) * ((end - begin) + 1));
	if (!trim)
		return (NULL);
	return (ft_cut(begin, end, trim, s1));
}
