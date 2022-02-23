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
	while (str[i] && str[i] != ' ' && is_operator(&str[i]) == 0 && str[i] != '$')
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

char	*del_dollar_2(char *str, char *var_name, char *ret, int len)
{
	int		first;
	int		i;
	int		j;
	
	first = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && first == 0)
		{
			if (!strncmp(&str[i + 1], var_name, len))
			{
				first = 1;
				i++;
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

char	*del_dollar(char *str, char *var_name, int len)
{
	char	*ret;
	
	ret = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!ret)
		return (NULL);
	return (del_dollar_2(str, var_name, ret, len));
}


char	*replace_dollar_2(char *str, char *new_var, char *ret, int pos)
{
	int	i;
	int	j;
	int	k;


	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (i == pos)
		{
			while (new_var[k])
			{
				ret[j] = new_var[k];
				k++;
				j++;
			}
		}
		ret[j] = str[i];
		i++;
		j++;
	}
	free(new_var);
	free(str);
	return (ret);
}

char	*replace_dollar(char **env, char *str, char *var_name, int pos)
{
	char *new_var;
	char *ret;

	new_var = NULL;
	ret = NULL;
	new_var = find_val_in_tab(env, var_name);
	if (!new_var)
		return (NULL);
	str = del_dollar(str, var_name, ft_strlen(var_name));
	ret = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(new_var) + 1)));
	if (!ret)
		return (NULL);
	free(var_name);
	return (replace_dollar_2(str, new_var, ret, pos));
}


char	*expand_dollar(char **env, char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '$')
		{
			var_name = cut_dollar(&str[i]);
			if (!var_name)
				return (NULL);
			if (ft_find_env_line(env, var_name) && str[i + 1] != '$')
			{
				str = replace_dollar(env, str, var_name, i);
			}
			else
			{
				str = del_dollar(str, var_name, ft_strlen(var_name));
			}
			i = 0;
		}
		i++;
	}
	return(str);
}

/* int	expand_cmd(t_token **lexer, char **env)
{

} */

/* int	main(int ac, char **av, char **envp)
{
	char	**env;
	(void)ac;
	(void)av;
	char *str;

	str = NULL;
	env = NULL;
	env = ft_create_env(envp);
	//str = replace_dollar(env, ft_strdup("salut ca va $USER et toi "), ft_strdup("USER"), 12);
	str = expand_dollar(env, ft_strdup("\"$USER$USER $$$ $LOL toi $\""));
	printf("%s\n", str);
	free(str);
	ft_free_tab_2d(env);
	return (0);
} */