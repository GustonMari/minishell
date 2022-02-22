#include "../includes/function.h"


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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		dest[j + i] = s2[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}

int	ft_count_slash(char *str)
{
	int	i;
	int	slash;

	i = 0;
	slash = 0;
	while (str[i])
	{
		if (str[i] == '/')
			slash++;
		i++;
	}
	return (slash);
}