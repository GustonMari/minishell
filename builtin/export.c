
#include "../includes/function.h"

/* char	**ft_swap_2d(char **tab)
{
	char	*a;
	char	*b;
	char	*tmp;


} */

int		ft_print_export_no_arg(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

char	**bubble_sort_tab_2d(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < ft_count_line(tab))
	{
		j = i + 1;
		while (j < ft_count_line(tab))
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = ft_strdup(tab[i]);
				if (!tmp)
					return (NULL);
				free(tab[i]);
				tab[i] = ft_strdup(tab[j]);
				if (!tab[i])
					return (NULL);
				free(tab[j]);
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void	ft_export_no_arg(char **env)
{
	char	**env_sorted;

	env_sorted = bubble_sort_tab_2d(ft_strdup_2d(env));
	if (!env_sorted)
		return ;
	ft_print_export_no_arg(env_sorted);
	ft_free_tab_2d(env_sorted);
}

//ft_export_add

char	**ft_export(char **env, char *str)
{
	char	**new_env;
	int		line;
	int		i;

	i = 0;
	line = ft_count_line(env);
	new_env = malloc(sizeof(char *) * (line + 2));
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

/* Trouve le nom de la variable d'environemment passe en parametre
exemple : si str --> PWD=lolilol
on va retourner PWD */

char	*find_name_val(char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	while (j < i)
	{
		name[j] = str[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

/* Cette fonction va renvoyer la valeur d'une ligne d'une
variable d'environnement donnee, exemple :
str --> PWD=lolilol
ON renvoie --> lolilol*/

char	*find_val_in_line(char *str)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	i++;
	val = malloc(sizeof(char) * (ft_strlen(&str[i]) + 2));
	if (!val)
		return (NULL);
	while (str[i])
	{
		val[j] = str[i];
		i++;
		j++;
	}
	val[j] = '\0';
	return (val);
}

/* char	**ft_export_change(char **env, char *str)
{

}

char	**ft_export(char **env, char *str)
{
	if (find_val_in_tab(env, str) != NULL)
	{
		env = ft_export_change(env, str);
	}
	else
	{
		env = ft_export_add(env, str);
	}
} */

/* int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	**env;

	env = ft_create_env(envp);
	ft_export_no_arg(env);
	ft_free_tab_2d(env);
} */