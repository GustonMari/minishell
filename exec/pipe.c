
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

pid_t	fork_pipe(int fd_0, int fd_1)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (fd_0 != 0)
		{
			dup2(fd_0, STDIN_FILENO);
			close(fd_0);
		}
		if (fd_1 != 1)
		{
			dup2(fd_1, STDOUT_FILENO);
			close(fd_1);
		}
	}
	return (pid);
}



int	execute_last(t_command *all_cmd, char **env, int fd_0, int fd_1)
{
	int	pid;

	pid = fork_pipe(fd_0, fd_1);
	if (pid == 0)
		ft_exec(env, all_cmd->cmd_to_exec);
	return (0);
}

int execute_pipe(t_command *all_cmd, char **env, int nb_cmd)
{
	int		fd[2];
	int		fd_0;
	int		fd_1;
	int		i;
	//int		status;
	pid_t	pid;

	i = 0;
	fd_0 = STDIN_FILENO;
	fd_1 = STDOUT_FILENO;
	while (all_cmd && (i < nb_cmd -1))
	{
		if (pipe(fd) < 0)
			return (-1);
		pid = fork_pipe(fd_0, fd[1]);
		if (pid == 0)
			ft_exec(env, all_cmd->cmd_to_exec);
		close(fd[1]);
		fd_0 = fd[0];
		all_cmd = all_cmd->next->next;
		i++;
	}
	redirection(all_cmd, &fd_0, &fd_1);
	execute_last(all_cmd, env, fd_0, fd_1);
	wait_pipe(nb_cmd);
	return (0);
}

/* int execute_pipe(t_command *all_cmd, char **env, int nb_cmd)
{
	int		fd[2];
	int		fd_0;
	int		fd_1;
	int		i;
	pid_t	pid;

	i = 0;
	fd_0 = STDIN_FILENO;
	while (all_cmd && i < nb_cmd)
	{
		
		if (pipe(fd) < 0)
			return (-1);
		if(all_cmd->next && all_cmd->next->type == CHV_R)
		{
			fd_1 = open(all_cmd->next->next->cmd_to_exec[0], O_WRONLY | O_CREAT | O_TRUNC, 00777);
			execute_last(all_cmd, env, fd_0, fd_1);
			if (all_cmd->next->next)
				all_cmd = all_cmd->next->next;
		}
		else
		{
			fd_1 = fd[1];
			pid = fork_pipe(fd_0, fd_1);
			if (pid == 0)
				ft_exec(env, all_cmd->cmd_to_exec);
			close(fd[1]);
			fd_0 = fd[0];
		}
		if (all_cmd && all_cmd->next && all_cmd->next->next)
			all_cmd = all_cmd->next->next;
		i++;
	}
	execute_last(all_cmd, env, fd_0, STDOUT_FILENO);
	wait_pipe(nb_cmd);
	return (0);
} */

/* int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_token *temp;
	t_token	*expanded;
	t_command *cmd_all;
	(void)cmd_all;
    char **env;
	
	env = ft_create_env(envp);
    char *line = ft_strdup("ls | ls");
	temp = lexer(line);
	expanded = expand_all(env, temp);
	trim_all(&expanded);
	cmd_all = token_to_cmd(expanded);
    execute_pipe(cmd_all, env, count_cmd_list(cmd_all));
    //ft_dispatch(cmd_all, env);
	//print_cmd(&cmd_all);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);

	int	test = 0;
	scanf("%d", &test);
	printf("test = %d\n", test);
    return (0);
} */