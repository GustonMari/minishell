/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:02:11 by gmary             #+#    #+#             */
/*   Updated: 2022/03/02 15:11:11 by gmary            ###   ########.fr       */
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
		cd_error(str, 0);
		return (-1);
		/* exit(1); */
	}
	return (0);
}

/*
	retour au bercail
*/

int	ft_home(char **env)
{
	char	*path;
	char	*old_pwd;

	path = find_val_in_tab(env, "HOME");
	if (path)
	{
		if (ft_check_cd(path))
			return (-1);
		chdir(path);
	}
	else
		chdir(getenv("HOME="));
	old_pwd = find_val_in_tab(env, "PWD");
	ft_change_env_val(env, "PWD", ft_pwd_return());
	ft_change_env_val(env, "OLDPWD", old_pwd);
	free(old_pwd);
	return (0);
}


//MAIN CD FUNCTION

int	ft_cd(char **full_cmd, char **env)
{
	char	*old_pwd;
	
	if (ft_count_line(full_cmd) > 2)
	{
		cd_error(full_cmd[1], 1);
	}
	if (ft_count_line(full_cmd) ==1 || !ft_strcmp(full_cmd[1], "~"))
		return(ft_home(env));
	if (ft_check_cd(full_cmd[1]))
		return (-1);
	old_pwd = find_val_in_tab(env, "PWD");
	if (chdir(full_cmd[1]) == -1)
		printf("Error chdir not working");
	ft_change_env_val(env, "PWD", ft_pwd_return());
	ft_change_env_val(env, "OLDPWD", old_pwd);
	free(old_pwd);
	//exit (0);
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
