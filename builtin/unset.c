#include "../includes/function.h"




/*
	copie tt le tab en sautant une ligne indique au prealable (supprime la variable env envoye en param)
	et return le nouveau tab d'env
*/

char	**ft_unset_line(char **env, char *to_del)
{
	int		i;
	int		line;
	char	**dest;
	int		j;

	
	i = 0;
	line = ft_count_line(env);
	dest = malloc(sizeof(char *) * (line));
	if (!dest)
		return (NULL);
	j = -1;
	while (++j < line)
	{
		if (is_var_in_line(env[j], to_del, ft_strlen(to_del)))
		{	
			dest[i] = ft_strdup(env[j]);
			if (!dest[i])
				return (NULL);
			i++;
		}
	}
	dest[i] = NULL;
	//ft_free_tab_2d(env);
	return (dest);
}

char	**ft_unset(char **env, char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		env = ft_unset_line(env, full_cmd[i]);
		if (!env)
			return (NULL);
		i++;
	}
	return (env);
}

/* int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	**env;
	char *full_cmd[] = {"unset", "PWD", NULL};

	env = ft_create_env(envp);
	env = ft_unset(env, full_cmd);
	ft_print_env(env);
	//ft_print_env(ft_unset(env, full_cmd));
	ft_free_tab_2d(env);
} */
