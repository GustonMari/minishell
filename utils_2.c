#include "function.h"


char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_strdup_2d(char **srcs)
{
	int		i;
	int		line;
	char	**dest;

	i = 0;
	line = ft_count_line(srcs);
	dest = malloc(sizeof(char *) * (line + 1));
	if (!dest)
		return (NULL);
	while (i < line)
	{
		dest[i] = ft_strdup(srcs[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int		ft_count_line(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
