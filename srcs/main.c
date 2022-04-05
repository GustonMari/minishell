/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:11:10 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/05 17:53:33 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile with: gcc -lreadline test.c
// for MacOs: to have the path of readlin lib:
//1)brew --prefix readline 2)find the right folder
/*
	OR
	-lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
*/
#include "includes/function.h"

//->ctr + c => SIGINT(interuption), ctrl + d => SIGHUP(fin de connexion)
//Do you want to quit [y/n] ? ca peut etre tres cool
// pas reussi a gerer bien ctrl=D
// fork == 0 =>childprocess
//attention lors dun fork la position
//des fichier nest pas duppliquer dou gettenv!!
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
	AVANT DAVOIR ECRIT SUR LE CLAVIER
*/

void	exit_process(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
		return ;
	}
	exit(0);
}

int	signal_main(void)
{
	if (signal(SIGINT, &exit_process) == SIG_ERR)
	{
		ft_putstr_fd("Error\n", 2);
		return (FALSE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("Error\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

char	**main_bis(int ac, char **av, char **envp)
{
	char	**env;

	(void)ac;
	(void)av;
	env = NULL;
	if (isatty(STDIN_FILENO) == TRUE)
	{
		printf("ADIOS\n");
		exit (0);
	}
	if (!envp)
	{	
		ft_putstr_fd("\n\e[1;91m- Need ENVP -\e[0m\n", 1);
		g_status = 1;
		exit(1);
	}
	g_status = errno;
	env = ft_create_env(envp);
	env = shell_lvl(env);
	return (env);
}

int	g_status;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**env;

	line = NULL;
	env = main_bis(ac, av, envp);
	while (42)
	{
		if (signal_main() == FALSE)
			return (0);
		else
			line = readline(BBLU "minishell> " CRESET);
		if (!line)
		{
			write(2, "\n", 1);
			rl_clear_history();
			ft_free_tab_2d(env);
			break ;
		}
		if (line && *line)
		{	
			add_history(line);
			env = manage_line(env, line);
		}
	}
	exit (g_status);
}
