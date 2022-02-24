#include "../includes/function.h"

char	*del_quote(char *str, int pos_a, int pos_b)
{
	int	i;
	int	j;
	char *ret;

	ret = NULL;
	i = 0;
	j = 0;
	ret = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	/* ret = malloc(sizeof(char) * (ft_strlen(str) + 2)); */
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (i == pos_a)
			i++;
		if (i == pos_b)
			i++;
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	free(str);
	return (ret);
}

char	*trim_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE)
		{
			j = find_next_quote(&str[i]);
			str = del_quote(str, i, (j + i - 1));
			if (!str)
				return (NULL);
			i += j;
		}
		i++;
	}
	return (str);
}

int	main()
{
	char	*str = NULL;
	char	*ret = NULL;
	str = ft_strdup("\" \' sa\"lut\"cava\"ou i  i\" sal\"");
	printf("str = %s\n", str);
	ret = trim_quote(str);
	printf("%s\n", ret);
	free(ret);
	return (0);
}
