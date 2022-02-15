/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:02:11 by gmary             #+#    #+#             */
/*   Updated: 2022/02/15 19:29:05 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

/*
	X_OK check si file existe + tte les permisions
*/
char	*ft_cpy_val_var_env(char *var, char *find)
{
/* 	int		len_var; */
	int		len_find;
	char	*val_var;

	/* len_var = ft_strlen(var); */
	len_find = ft_strlen(find);
	val_var = ft_strdup(&var[len_find + 1]);
	if (!val_var)
		return (NULL);
	return (val_var);
	
}

char	*ft_get_path(char **tab, char *find)
{
	int		i;
	
	i = 0;
	while (tab[i])
	{
		//changer nom function en dessous
		if (!ft_ncmp_unset(tab[i], find, ft_strlen(find)))
			return (ft_cpy_val_var_env(tab[i], find));
		i++;
	}
	return (NULL);
}

int	ft_check_cd(char *str)
{
	if (access(str, X_OK) == -1)
	{
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
/* 	char	*buff; */
	/* char	*home; */
	char	*ret;
/* 	char	*tmp; */

/* 	buff = NULL; */
	ret = ft_get_path(env, "HOME");
	if (ret)
		chdir(ret);
	else
		chdir(getenv("HOME="));
	printf("%s\n", ret);
	/* 	home = getcwd(buff, BUFFER_SIZE);
	free(home);
	 printf("%s\n", getcwd(buff, BUFFER_SIZE)); */
	return (0);
}

//MAIN CD FUNCTION

int	ft_cd(char *str, char **env)
{
	char	*buff;

	buff = NULL;
	if (!*str || !ft_strcmp(str, "~"))
		return(ft_home(env));
	if (ft_check_cd(str))
		return (1);
	if (chdir(str) == -1)
		printf("Error chdir not working");
	printf("%s\n", getcwd(buff, BUFFER_SIZE));
	//change PWD & OLDPWD ??
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_home(envp);
}