#include "../includes/function.h"

char	*replace_interrogation(char *str, int pos, t_to_clean *clean, char *var_name)
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
	if (!status)
	{
		//WARNING
		free(var_name);
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	dest = malloc(sizeof(char) * (ft_strlen(str) - 1 + ft_strlen(status)));
	if (!dest)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
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
	//WARNING status et str ETTTTTTT VAR_NAME 
	free(status);
	free(str);
	//if (var_name)
	//	free(var_name);
	return (dest);
}

/* int g_status = 4;

int	main()
{
	printf("%s\n", replace_interrogation(ft_strdup("  $? $USER"), 2));
	return (0);
} */