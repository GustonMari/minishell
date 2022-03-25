#include "../includes/function.h"

char	*ft_cpy_val_var_env(char *var, char *find)
{
	int		len_find;
	char	*val_var;

	len_find = ft_strlen(find);
	val_var = ft_strdup(&var[len_find + 1]);
	if (!val_var)
		return (NULL);
	return (val_var);
}

/*
		Cherche dans tout le tableau et retourne la valeur de find
		exemple: find = HOME la fonction renverra /mnt/nfs/homes/gmary
*/

char	*find_val_in_tab(char **tab, char *find)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!is_var_in_line(tab[i], find, ft_strlen(find)))
			return (ft_cpy_val_var_env(tab[i], find));
		i++;
	}
	return (NULL);
}

/*
	remplace la valeur de la variable d'environement 
	par exmple si on veut remplacer pwd
	ou autre
*/

char	*ft_rpl_val_var_env(char *var, char *new_val)
{
	int		i;
	char	*ret;

	i = 0;
	while (var[i] != '=')
		i++;
	var[i + 1] = '\0';
	ret = ft_strjoin(var, new_val);
	free(var);
	return (ret);
}


/*
	change value de PWD et OLDPWD dans 
*/

int	ft_change_env_val(char **env, char *var, char *new_val)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!is_var_in_line(env[i], var, ft_strlen(var)))
		{
			env[i] = ft_rpl_val_var_env(env[i], new_val);
			printf("env = %s\n", env[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
	Permet de savoir si la variable est presente dans lenvironement 
*/
int	is_var_in_line(char *str, char *to_del, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str[i] && str[i] == to_del[i] && i < n - 1)
		i++;
	if (((unsigned char)str[i] - (unsigned char)to_del[i] == 0)
		&& (str[i + 1] == '='))
		return (0);
	else
		return (1);
}

/* int main(int argc, char **argv, char **envp)
{
	char	**env;
	(void)argc;
	(void)argv;
	char *str = "PWD=lolilol";
	char *name;
	char *val;
	char *ret;

	env = ft_create_env(envp);
	name = find_name_val(str);
	val = find_val_in_line(str);
	ret = find_val_in_tab(env, name);
	ft_change_env_val(env, name, val);
	ft_print_env(env);
	free(name);
	free(val);
	free(ret);
	ft_free_tab_2d(env);
} */