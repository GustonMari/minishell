/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:02:11 by gmary             #+#    #+#             */
/*   Updated: 2022/02/14 16:23:02 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

/*
	X_OK check si file existe + tte les permisions
*/
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

int	ft_home(void)
{
	char	*buff;

	chdir(getenv("HOME="));
	printf("%s\n", getcwd(buff, BUFFER_SIZE));
	return (0);
}

//MAIN CD FUNCTION

int	ft_cd(char *str)
{
	char	*buff;

	if (!*str || !ft_strcmp(str, "~"))
		return(ft_home());
	if (ft_check_cd(str))
		return (1);
	if (chdir(str) == -1)
		printf("Error chdir not working");
	printf("%s\n", getcwd(buff, BUFFER_SIZE));
	//change PWD & OLDPWD ??
	return (0);
}