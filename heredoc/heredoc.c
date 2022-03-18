#include "../includes/function.h"



/*Cette fonction permet de remplir le fichier 
temporaire tout en respecant les regles de priorite du heredoc*/

void	fill_heredoc_file(char **stop, char **env, int is_expand)
{
	char	*line = NULL;
	int		fd;
	int		i;
	int 	begin;
	
	begin = 0;
	i = 0;
	fd = create_heredoc_file();
	//line = NULL;
	while (1)
	{
		if (signal_heredoc(stop, line))
		{
			ft_free_tab_2d(stop);
			close(fd);
			printf("on exit\n");
			exit(g_status);
		}
		else
			line = readline("> ");

		//Gerer les signaux et bien check la valeur de retour de exit

		//if (signal_heredoc(stop, line))
		//	break ;
		//printf("line %s\n", line);
		//printf("stop = %s\n", stop[i]);
		if (stop[i] && !ft_strcmp(line, stop[i]))
		{
			if (stop[i + 1] == NULL)
			{
				free(line);
				break ;
			}
			i++;
		}
		if (is_expand == TRUE)
			line = expand_dollar(env, line);
		begin = start_heredoc_one(stop, begin);
		if (begin == 1)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		if (line)
			free(line);
		begin = start_heredoc_more(stop, i);
	}
	ft_free_tab_2d(stop);
	close(fd);
}

/*Compte le nombre de D_CHV_L entre deux pipe*/

int	count_nb_D_CHV_L_between_pipe(t_command *all_cmd)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_CHV_L)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/*Permet de creer le tableau a double dimension contenant les
limitor, chaque dimension en contient un.*/

char	**create_tab_stop(t_command *all_cmd)
{
	t_command	*tmp;
	char		**stop;
	int			i;

	i = 0;
	tmp = all_cmd;
	stop = NULL;
	stop = malloc(sizeof(char *) * (count_nb_D_CHV_L_between_pipe(tmp) + 1));
	if (!stop)
		return (NULL);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_CHV_L)
		{
			stop[i] = ft_strdup(tmp->next->cmd_to_exec[0]);
			if (!stop[i])
				return (NULL);
			i++;
		}
		tmp = tmp->next;
	}
	stop[i] = NULL;
	return (stop);
}

int	launch_heredoc(t_command *all_cmd, char **env)
{
	char	**stop;
	int		is_expand;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		stop = NULL;
		stop = create_tab_stop(all_cmd);
		if (!stop)
			return (-1);
		if(is_expand_heredoc(stop) == TRUE)
			is_expand = TRUE;
		else
			is_expand = FALSE;
		stop = trim_quote_stop(stop);
		if (!stop)
			return (-1);
		fill_heredoc_file(stop, env, is_expand);
		exit(0);
	}
	else
	{
		//fprintf(stderr, "on rentre\n");
		waitpid(pid, &status, 0);
		//fprintf(stderr, "ON sort\n");
	}
		
	return (0);
}

/* int	launch_heredoc(t_command *all_cmd, char **env)
{
	char	**stop;
	int		is_expand;
	pid_t	pid;
	
	stop = NULL;
	stop = create_tab_stop(all_cmd);
	if (!stop)
		return (-1);
	if(is_expand_heredoc(stop) == TRUE)
		is_expand = TRUE;
	else
		is_expand = FALSE;
	stop = trim_quote_stop(stop);
	if (!stop)
		return (-1);
	fill_heredoc_file(stop, env, is_expand);
	return (0);
} */


/*Fonction qui nous permet de savoir si la derniere redirection
est un double chevron a gauche.
Si c'est un Double chevron gauche, ca renvoi 0*/

int	priorities_D_CHV_L(t_command *all_cmd)
{
	t_command	*tmp;
	int			type;

	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_CHV_L || tmp->type == CHV_L)
			type = (int)tmp->type;
		tmp = tmp->next;
	}
	if (type == D_CHV_L)
		return (0);
	else
		return (1);
}


/* int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_token *temp = NULL;
	t_token	*expanded = NULL;
	t_command *cmd_all = NULL;
	cmd_all = NULL;
    char **env = NULL;
	
	env = ft_create_env(envp);
    char *line = ft_strdup("ls << ls < pouet << lol");
	temp = lexer(line);
	expanded = expand_all(env, temp);
	cmd_all = token_to_cmd(expanded);
	printf("Prio = %d\n", priorities_D_CHV_L(cmd_all));
    //ft_dispatch(cmd_all, env);
	//ft_lstclear(&expanded, free);
	//ft_cmd_clear(&cmd_all);
	//ft_free_tab_2d(env);
    return (0);
} */


/* int main()
{
	char *tab[] = {"mdr", "ca va", "yes", "pouet", NULL};
	fill_heredoc_file(tab);
	return (0);
} */

