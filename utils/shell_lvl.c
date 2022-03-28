#include "../includes/function.h"

char	**shell_lvl(char **env)
{
	char	*number;
	char	*ret;
	char	*to_export;

	ret  = find_val_in_tab(env, "SHLVL");
	if (ret == NULL)
	{
		number = ft_itoa(0);
		if (!number)
			return (NULL);
	}
	else
	{
		number = ft_itoa(ft_atoi(ret) + 1);
		if (!number)
			return (NULL);
		
	}
	to_export = ft_strjoin_free("SHLVL=", number, 2);
		if (!to_export)
			return (NULL);
	free(ret);
	printf("to export= %s\n", to_export);
	ft_export(env, to_export);
	return (env);
}
