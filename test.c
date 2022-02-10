/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:31:34 by gmary             #+#    #+#             */
/*   Updated: 2022/02/10 09:47:29 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile with: gcc -lreadline test.c
// for MacOs: to have the path of readlin lib:
//1)brew --prefix readline 2)find the right folder
/*
	OR
	gcc test.c ft_strcmp.c -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
*/
#include "function.h"

//->ctr + c => SIGINT(interuption), ctrl + d => SIGHUP(fin de connexion)
//Do you want to quit [y/n] ? ca peut etre tres cool
// pas reussi a gerer bien ctrl=D
// fork == 0 =>childprocess
//attention lors dun fork la position des fichier nest pas duppliquer dou gettenv!!
/*
	coller un perror apres le exec pour check si le pgm a bien ete execute
	en attendant le parent wait() que le le fils se suicide a cause du exec
*/

/*
	1) rl_on_new_line cree une ligne vide, 
	2) rl_replace permet de remplir la ligne avec du text(rl_line_buffer)
	 (ici rien "")
	3) rl_redisplay permet de faire apparaitre le prompt 
	et dinserer apres le text de replace 
	AVANT DAVOIR ECRI SUR LE CLAVIER
*/
void	exit_process(int sig)
{

	if (sig == SIGINT)
	{
		//write(1, "\n\e[1;91m- SIGINT -\n", 20);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (sig == SIGQUIT)
		write(1, "\n\e[1;91m- SIGQUIT -\n", 20);
	exit(0);
}

int main()
{
	char	*line;
	kill();
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
			//clear history si il y en avait un
			write(2, "\n\e[0;35mctrl+D used\n", 21);
			break ;
		}
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			rl_clear_history();
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
