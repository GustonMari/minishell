/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:27:53 by gmary             #+#    #+#             */
/*   Updated: 2022/02/10 11:12:47 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

# define BUFFER_SIZE 55

int main(void)
{
	char	buff[BUFFER_SIZE];
	char	*ret;
	
	chdir("/mnt/nfs/homes/gmary/Documents/TAFF/minishell/salut");
	ret = getcwd(buff, BUFFER_SIZE);
	//if (getcwd(buff, BUFFER_SIZE) == NULL)
	if (ret == NULL)
	{
		if (errno = ERANGE)
			printf("ERANGE ERROR");
		exit(0);
	}
	else
		printf("%s\n", ret);
	ret = getcwd(buff, BUFFER_SIZE);
		//printf("%s\n", buff);
	//free(buff);
	return (0);
}