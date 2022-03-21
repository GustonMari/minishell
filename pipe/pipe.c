#include "../includes/function.h"


int	count_cmd_list(t_command *all_cmd)
{
	int			count;
	t_command	*tmp;

	tmp = all_cmd;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/*Compte le nombre de commande entre avant qu'il y ai
une redirection*/

int	count_cmd_between_pipe(t_command *all_cmd)
{
	int			count;
	t_command	*tmp;

	tmp = all_cmd;
	count = 0;
	while (tmp && !is_redirection_type(tmp))
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void ft_pipe(int first, int last, int *sortie)
{
	int pfd[2];

	if (!first)
	{
		dup2(*sortie, 0);
		close(*sortie);
	}
	if (!last)
	{
		//fprintf(stderr, "pouet\n");
		if (pipe(pfd) == -1)
			ft_putstr_fd("Erreur pipe\n", 2);
		else
		{
			dup2(pfd[1], 1);
			close(pfd[1]);
			*sortie = pfd[0];
		}
	}
}

/*Retourne 1 si c'est la derniere commande et qu'il n'y a pas de chevron droit
*/

int	is_last_cmd(t_command *all_cmd)
{
	t_command	*tmp;

	tmp = all_cmd;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == CHV_R || tmp->type == D_CHV_R)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int execute_pipe(t_command *all_cmd, char **env, int nb_cmd, int in)
{
	int			status;
	(void)status;
	int		out;
	int		i;
	int		save[2];
	int		ret;
	(void)in;
	(void)nb_cmd;

	ret = -1;
	i = 0;
	if (!all_cmd)
		return (0);
	out = -1;
	while (all_cmd)
	{
		save[0] = dup(0);
		save[1] = dup(1);
		//if (count_nb_D_CHV_L_between_pipe(all_cmd) != 0)
		//	launch_heredoc(all_cmd, env);
		ft_pipe(i == 0, is_last_cmd(all_cmd), &out);
		ret = redirection_manager(all_cmd);
		if (ret == -1)
		{
			dup2(save[0], 0);
			close(save[0]);
			dup2(save[1], 1);
			close(save[1]);
			//Il faut exit, le malloc s'est mal passe
			exit(1);
		}
		else if (ret == -2)
		{
			//regarder g_status
			dup2(save[0], 0);
			close(save[0]);
			dup2(save[1], 1);
			close(save[1]);
			g_status = 1;
		}
			
		//signal_in_cmd();
		else
			ft_exec(env, all_cmd->cmd_to_exec, out);
		//fprintf(stderr, "salut\n");
		redirection_clean(all_cmd);
		count_all_between_pipe(&all_cmd);
		dup2(save[0], 0);
		close(save[0]);
		dup2(save[1], 1);
		close(save[1]);
		i++;
	}
	wait_pipe();
	return (0);
}


/* int execute_pipe(t_command *all_cmd, char **env, int nb_cmd, int in)
{
	int		fd[2];
	int		out;
	int		i;
	//int		status;
	pid_t	pid;

	i = 0;
	if (!all_cmd)
		return (0);
	out = STDOUT_FILENO;
	while (all_cmd && (i < nb_cmd -1))
	{
		if (pipe(fd) < 0)
			return (-1);
		pid = fork_pipe(in, fd[1]);
		if (pid == 0)
			ft_exec(env, all_cmd->cmd_to_exec);
		close(fd[1]);
		in = fd[0];
		all_cmd = all_cmd->next->next;
		i++;
	}
	redirection(all_cmd, &in, &out, env);
	execute_last(all_cmd, env, in, out);
	wait_pipe(nb_cmd);
	count_all_between_pipe(&all_cmd);
	if (all_cmd)
		execute_pipe(all_cmd, env, count_cmd_between_pipe(all_cmd), in);
	return (0);
} */

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
    char *line = ft_strdup("ls >> ls > pouet > lol");
	temp = lexer(line);
	expanded = expand_all(env, temp);

	cmd_all = token_to_cmd(expanded);
    ft_dispatch(cmd_all, env);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	ft_free_tab_2d(env);
    return (0);
} */