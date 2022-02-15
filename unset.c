#include "function.h"


int	ft_ncmp_unset(char *str, char *to_del, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str[i] && str[i] == to_del[i] && i < n - 1)
		i++;
	if (((unsigned char)str[i] - (unsigned char)to_del[i] == 0) && (str[i + 1] == '='))
		return (0);
	else
		return (1);
}

/*
	copie tt le tab en sautant une ligne indique au prealable (supprime la variable env envoye en param)
	et return le nouveau tab d'env
*/
char	**ft_create_unset(char **srcs, char *to_del)
{
	int		i;
	int		line;
	char	**dest;
	int		j;

	j = 0;
	i = 0;
	line = ft_count_line(srcs);
	dest = malloc(sizeof(char *) * (line));
	if (!dest)
		return (NULL);
	while (j < line)
	{
		if (ft_ncmp_unset(srcs[j], to_del, ft_strlen(to_del)))
		{	
			dest[i] = ft_strdup(srcs[j]);
			if (!dest[i])
				return (NULL);
			i++;
		}
		j++;

	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_unset(char **env)
{
	char	**new_tab;

	new_tab = ft_create_unset(env, "QT_ACCESSIBILITY");
	return (new_tab);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	**env;

	env = ft_create_env(envp);
	ft_print_env(ft_unset(env));
	ft_free_tab_2d(env);
}