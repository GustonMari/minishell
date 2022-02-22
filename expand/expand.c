#include "../includes/function.h"

/*Prend une string qui commence par $, si par exemple on a "$USER pouet"
On commence a i = 1 pour etre sur le debut du nom de la var d'env. On veut copier
USER et le renvoyer.
*/

char	*cut_dollar(char *str)
{
	int	i;
	char	*var_name;

	i = 1;
	while (str[i] && str[i] != ' ' && is_operator(&str[i]) == 0)
		i++;
	var_name = malloc(sizeof(char) * (i));
	if (!var_name)
		return (NULL);
	var_name = ft_strncpy(var_name, &str[1], i - 1);
	return (var_name);
	
}

/*
	permet de supprimer une variable commenceant par $ (var_name) dans une string donne
*/

char	*del_dollar(char *str, char *var_name, int len)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (!strncmp(&str[i], var_name, len))
			{
				i += len;
			}
		}
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	free(str);
	return (ret);
}

char	*replace_dollar(char **env, char *str, char *var_name, int pos)
{
	int	i;
	int	j;
	char *new_var;
	char *ret;

	i = 0;
	j = 0;
	new_var = find_val_in_tab(env, var_name);
	if (!new_var)
		return (NULL);
	str = del_dollar(str, var_name, ft_strlen(var_name));
	ret = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(new_var) + 1) - (ft_strlen(var_name) + 1)));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (i == pos)
		{
			while (*new_var)
			{
				ret[j] = *new_var;
				new_var++;
				j++;
			}
			i++;
		}
		ret[j] = str[i];
		i++;
		j++;
	}
	//free(str);
	return (ret);
}


/* char	*expand_dollar(char **env, char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == ' ')
		{
			var_name = cut_dollar(&str[i]);
			if (!var_name)
				return (NULL);
			if (ft_find_env_line(env, var_name))
			{
				replace_dollar(env, str, var_name, i);
			}
			else
			{
				str = del_dollar(str, var_name, ft_strlen(var_name));
			}
			i = 0;
		}
		i++;
	}
}
 */
/* int	expand_cmd(t_token **lexer, char **env)
{

} */

int	main(int ac, char **av, char **envp)
{
	char	**env;
	(void)ac;
	(void)av;

	env = ft_create_env(envp);
	printf("%s\n", replace_dollar(env, ft_strdup("salut ca va $USER et toi "), "USER", 12));
	//ft_free_tab_2d(env);
	return (0);
}