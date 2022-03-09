
#include "../includes/function.h"


int	count_cmd_list(t_command *all_cmd)
{
	int			count;
	t_command	*tmp;

	tmp = all_cmd;
	count = 0;
	while (tmp /* && is_redirection_type(tmp) */)
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

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

pid_t	fork_pipe(int in, int out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		/* if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		} */
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
	}
	return (pid);
}



int	execute_last(t_command *all_cmd, char **env, int in, int out)
{
	int	pid;

	pid = fork_pipe(in, out);
	if (pid == 0)
		ft_exec(env, all_cmd->cmd_to_exec);
	return (0);
}

int execute_pipe(t_command *all_cmd, char **env, int nb_cmd, int in)
{
	int		fd[2];
	//int		in;
	int		out;
	int		i;
	//int		status;
	pid_t	pid;

	i = 0;
	//in = STDIN_FILENO;
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
	redirection(all_cmd, &in, &out);
	execute_last(all_cmd, env, in, out);
	//printf("lst = %s\n", all_cmd->cmd_to_exec[0]);
	wait_pipe(nb_cmd);
	if (all_cmd->next->next->next->next)
		execute_pipe(all_cmd->next->next->next->next, env, 1, in);
	return (0);
}


int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_token *temp;
	t_token	*expanded;
	t_command *cmd_all;
	(void)cmd_all;
    char **env;
	
	env = ft_create_env(envp);
    char *line = ft_strdup("ls | wc > pouet | wc");
	temp = lexer(line);
	expanded = expand_all(env, temp);

	cmd_all = token_to_cmd(expanded);
    ft_dispatch(cmd_all, env);
    //ft_dispatch(cmd_all, env);
	//print_cmd(&cmd_all);
	//ft_lstclear(&expanded, free);
	//t_cmd_clear(&cmd_all);
    return (0);
}