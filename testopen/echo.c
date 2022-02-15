/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:59:02 by gmary             #+#    #+#             */
/*   Updated: 2022/02/14 18:52:15 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"


//ici le arg correspond au -n si il n'y a pas de n on arg = 0 sinon = 1

int	ft_check_double(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

/*
			ATTENTION: surement ne pas utiliser printf pour les redirections de type 2> 
			mais dapres discord on ne doit pas gerer ce cas ci
			- 47 => simple quote ;)
			- comment gerer """" "'" etc...
			- faire en amont avec les tokens le predecoupage???
			-surement faire pleins de petit echo, comme pour les cas comme ceci:
			echo "salut toi" | echo "oui oui" => ou pas besoin car process situe dans le child ??
			- dapres le tuto il faudrait plus print tant que lon tombe pas sur un | ce qui est plustot 
			pratique sauf si lon tombe sur echo " salut toi | tu manges buen"
*/

int	ft_echo(char *str, int arg)
{
	if (ft_check_double(str, (char)47)) //a bien mettre en premier car cest les simple quote qui annule tout
		printf("%s", str);
	if (arg == 0)
		printf("\n");
	return (0);
}

int		main(void)
{
	char str[] = "echo 'ca va bien'";
	ft_echo(str,0);
	return (0);
}