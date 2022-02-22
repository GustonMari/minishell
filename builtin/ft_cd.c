/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:02:11 by gmary             #+#    #+#             */
/*   Updated: 2022/02/22 09:31:28 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"


/*
	X_OK check si file existe + tte les permisions
*/
int	ft_check_cd(char *str)
{
	if (access(str, X_OK) == -1)
	{
		//a changer virer fprintf
		perror("\e[0;31mError");
		ft_putstr_fd("\e[0m", 2);
		//perror((const char *)strerror(errno));
		//perror("\n");
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
	ft_change_env_val(env, "PWD", ft_pwd_return());
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
