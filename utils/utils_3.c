#include "../includes/function.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
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

char	*ft_strjoin_free(char *s1, char *s2, int del)
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
	i = -1;
	while (s2[++i])
		dest[j + i] = s2[i];
	dest[j + i] = '\0';
	if (del == 1)
		free(s1);
	if (del == 2)
		free(s2);
	return (dest);
}

static char	*ft_zero(void)
{
	char	*str;

	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char *s, int start, int len)
{
	char			*new;
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_zero());
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	while (i < start && s[i])
		i++;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (j < len && s[i])
	{
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

void	print_tab_2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}
