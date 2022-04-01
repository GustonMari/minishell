#include "../includes/function.h"

char	**shell_lvl(char **envp)
{
	char	*number;
	char	*ret;
	char	*to_export;
	char	**env;

	ret  = find_val_in_tab(envp, "SHLVL");
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
	env = ft_export(envp, to_export);
	free(to_export);
	//print_tab_2d(env);
	//ft_free_tab_2d(envp);
	return (env);
}
