/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:27:53 by gmary             #+#    #+#             */
/*   Updated: 2022/02/11 08:43:11 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

# define BUFFER_SIZE 46


int main(void)
{
	char	*buff = NULL;
	char	*ret;
	
	if (chdir("/Users/gustavemary/Documents/ProjetCode/VIM/CURSUS/r3/minishell/testopen") == -1)
		printf("Error");
	ret = getcwd(buff, BUFFER_SIZE);
	//"/mnt/nfs/homes/gmary/Documents/TAFF/minishell";
	//if (getcwd(buff, BUFFER_SIZE) == NULL)
	if (ret == NULL)
	{
		if (errno == ERANGE)
			printf("ERANGE ERROR");
		exit(0);
	}
	else
		printf("getcwd %s\n", ret);
	
	printf("getenv %s\n", getenv("PWD"));
	//et = getcwd(buff, BUFFER_SIZE);
		//printf("%s\n", buff);
	free(buff);
	free(ret);
	return (0);
}


/*
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int i = 0;

	while (envp)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
} 
*/

/*
int main(void)
{
	printf("%s\n", getenv("PWD"));
}
*/