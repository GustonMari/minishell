
#include "function.h"

char	**ft_export(char **env, char *str)
{
	char	**new_env;
	int		line;
	int		i;

	i = 0;
	line = ft_count_line(env);
	new_env = malloc(sizeof(char *) * line + 2);
	if (!new_env)
		return (NULL);
	while (i < line)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			//clear le tab JUSQUAU i
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	ft_free_tab_2d(env);
	return (new_env);
}
