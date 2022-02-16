/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:02:11 by gmary             #+#    #+#             */
/*   Updated: 2022/02/16 11:40:20 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

/*
	X_OK check si file existe + tte les permisions
*/
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
	int		i;
	
	i = 0;
	while (tab[i])
	{
		//changer nom function en dessous
		if (!is_var_in_line(tab[i], find, ft_strlen(find)))
			return (ft_cpy_val_var_env(tab[i], find));
		i++;
	}
	return (NULL);
}

int	ft_check_cd(char *str)
{
	if (access(str, X_OK) == -1)
	{
		//a changer virer fprintf
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}

/*
	retour au bercail
*/

int	ft_home(char **env)
{
	char	*path;

	path = find_val_in_tab(env, "HOME");
	if (path)
	{
		if (ft_check_cd(path))
			return (-1);
		chdir(path);
	}
	else
		chdir(getenv("HOME="));
	return (0);
}

/*
	remplace la valeur de la variable d'environement par exmple si on veut remplacer pwd
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
		//changer nom function en dessous
		if (!is_var_in_line(env[i], var, ft_strlen(var)))
		{
			env[i] = ft_rpl_val_var_env(env[i], new_val);
			printf("%s\n", env[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

//MAIN CD FUNCTION



int	ft_cd(char *str, char **env)
{
	char	*old_pwd;
	
	if (!*str || !ft_strcmp(str, "~"))
		return(ft_home(env));
	if (ft_check_cd(str))
		return (-1);
	old_pwd = find_val_in_tab(env, "PWD");
	if (chdir(str) == -1)
		printf("Error chdir not working");
	//change PWD & OLDPWD ??
	ft_change_env_val(env, "PWD", str);
	printf("------------------------------------------\n");
	ft_change_env_val(env, "OLDPWD", old_pwd);
	free(old_pwd);
	return (0);
}


/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_cd("/mnt/nfs/homes/gmary/Documents/TAFF", ft_create_env(envp));
	return (0);
} */
