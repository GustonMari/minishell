#include "../includes/function.h"



/*Cette fonction permet de remplir le fichier 
temporaire tout en respecant les regles de priorite du heredoc*/

void	fill_heredoc_file(char **stop, char **env, int is_expand, char *name)
{
	char	*line;
	int		fd;
	int		i;
	int 	begin;
	
	begin = 0;
	i = 0;
	line = NULL;
	fd = create_heredoc_file(name);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			g_status = 0;
			exit(g_status);
		}
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

int	launch_heredoc(t_command **all_cmd, char **env, char *name)
{
	char	**stop;
	int		is_expand;
	pid_t	pid;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (fprintf(stderr, "Error: %s\n", strerror(errno)));
	pid = fork();
	if (pid == 0)
	{
		signal_heredoc();
		stop = NULL;
		stop = create_tab_stop(*all_cmd);
		if (!stop)
			return (-1);
		if(is_expand_heredoc(stop) == TRUE)
			is_expand = TRUE;
		else
			is_expand = FALSE;
		stop = trim_quote_stop(stop);
		if (!stop)
			return (-1);
		fill_heredoc_file(stop, env, is_expand, name);
		exit(g_status);
	}
	else
		wait_pipe();
	if (g_status == 130)
		return (-2);
	return (0);
}

/*Trouve un nom de heredoc valide*/

char	*find_heredoc_name(void)
{
	static int i = 0;
	char	*name;

	name = NULL;
	while (1)
	{
		name = ft_strjoin_free(".heredoc", ft_itoa(i), 2);
		if (!name)
			return (NULL);
		if (access(name, F_OK) < 0)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}


/*Permet de remplacer << par < et le word suivant par
le nom du heredoc qui etait dispo*/

int	replace_heredoc(t_command **all_cmd, char *name)
{
	char	**d_chv;
	char	**name_2d;

	ft_free_tab_2d((*all_cmd)->cmd_to_exec);
	(*all_cmd)->type = CHV_L;
	d_chv = ft_calloc(sizeof(char *), 2);
	if (!d_chv)
		return (-1);
	d_chv[0] = ft_strdup("<");
	if (!d_chv[0])
	{
		free(d_chv);
		return (-1);
	}
	d_chv[1] = NULL;
	(*all_cmd)->cmd_to_exec = d_chv;
	if ((*all_cmd) && (*all_cmd)->next)
	{
		ft_free_tab_2d((*all_cmd)->next->cmd_to_exec);
		(*all_cmd)->next->type = WORD;
		(*all_cmd)->next->to_del = 1;
		name_2d = ft_calloc(sizeof(char *), 2);
		if (!name_2d)
			return (-1);
		name_2d[0] = name;
		name_2d[1] = NULL;
		(*all_cmd)->next->cmd_to_exec = name_2d;
	}
	else
		return (-1);
	return (0);
}

/*Fonction qui manage le heredoc*/

int	manage_heredoc(t_command **all_cmd, char **env)
{
	int			ret;
	t_command	*tmp;
	char		*name;

	ret = 0;
	tmp = *all_cmd;
	while (tmp)
	{
		if (tmp->type == D_CHV_L && tmp->next && tmp->next->type == WORD)
		{
			name = find_heredoc_name();
			if (!name)
				return (-1);
			ret = launch_heredoc(&tmp, env, name);
			replace_heredoc(&tmp, name);
			if (ret < 0)
				return (ret);
			count_all_between_pipe(&tmp);
		}
		else
			tmp = tmp->next;
	}
	return(0);
}


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

