#include "../includes/function.h"

char	*replace_interrogation(char *str, int pos)
{
	char	*dest;
	char	*status;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	status = ft_itoa(g_status);
	dest = malloc(sizeof(char) * (ft_strlen(str) - 1 + ft_strlen(status)));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (i == pos)
		{
			while (status[j])
			{
				dest[k] = status[j];
				j++;
				k++;
			}
			i += 2;
		}
		else
		{
			dest[k] = str[i];
			i++;
			k++;
		}
	}
	dest[k] = '\0';
	return (dest);
}

/* int g_status = 4;

int	main()
{
	printf("%s\n", replace_interrogation(ft_strdup("  $? $USER"), 2));
	return (0);
} */