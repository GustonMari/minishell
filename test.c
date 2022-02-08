/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:31:34 by gmary             #+#    #+#             */
/*   Updated: 2022/02/08 11:38:49 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile with: gcc -lreadline test.c

#include "function.h"

//->ctr + c => SIGINT(interuption), ctrl + d => SIGHUP(fin de connexion)
//Do you want to quit [y/n] ? ca peut etre tres cool
// pas reussi a gerer bien ctrl=D

void	exit_process(int sig)
{
	//(void)nothing;
	if (sig == SIGINT)
		write(1, "\n\e[1;91m- SIGINT -\n", 20);
	if (sig == SIGQUIT)
		write(1, "\n\e[1;91m- SIGQUIT -\n", 20);
	exit(0);
}

int main()
{
	char	*line;

	while (42)
	{
		if (signal(SIGINT, &exit_process) == SIG_ERR)
			return (fprintf(stderr, "Error: %s\n", strerror(errno)));
		if (signal(SIGQUIT, &exit_process) == SIG_ERR)
			return (fprintf(stderr, "Error: %s\n", strerror(errno)));
		else
			line = readline(BBLU "minishell> " CRESET);
		//obligatoire sinon segfault pour ctrl D est-ce que lon peut considerer ceci comme un sighandler
		if (!line)
		{
			write(2, "\n\e[0;35mctrl+D used\n", 21);
			break ;
		}
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			printf("%s- EXIT OK -\n", BHRED);
			return (0);
		}
		//on ne veut pas avoir de ligne vide dans l'historique ??
		if (line && *line)
		{	
			add_history(line);
			printf("%s\n", line);
		}
		if(line)
			free(line);
	}
	return 0;

}
