
#include "../includes/function.h"


int	count_cmd_list(t_command *all_cmd)
{
	int			count;
	t_command	*tmp;

	tmp = all_cmd;
	count = 0;
	while (tmp && (tmp->type == WORD || tmp->type == PIPE))
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

void	exit_NTM(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	/* printf("exited NTM\n"); */
}

int execute_pipe(t_command *all_cmd, char **env, int nb_cmd)
{
	int		fd[2];
	int		fd_0;
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	fd_0 = STDIN_FILENO;
	while (i < nb_cmd -1 && all_cmd)
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
	pid = fork_pipe(fd_0, STDOUT_FILENO);
	if (pid == 0)
		ft_exec(env, all_cmd->cmd_to_exec);
	i = 0;
	while (i < nb_cmd)
	{
		if (signal(SIGINT, &exit_NTM) == SIG_ERR)
			return (fprintf(stderr, "Error: %s\n", strerror(errno)));
		wait(&status);
		i++;
	}
	return (0);
}







/* int execute_pipe(t_command *all_cmd, char **env, int nb_cmd)
{
	int			i;
	int			fd[2];
	pid_t		pid1;
	pid_t		pid2;
	int			status;
	t_command	*tmp;
	int			fd_file; 

	fd_file = open("pouet", O_CREAT | O_WRONLY | O_TRUNC, 00666);
	if (fd_file < 0)
	{
		printf("Pb open file\n");
		return (-1);
	}
	tmp = all_cmd;
	i = 0;
	while (i < nb_cmd - 1 && tmp)
	{
		if (pipe(fd) < 0)
			return (-1);
		pid1 = fork();
		if (pid1 < 0)
			return (-1);
		if (pid1 == 0)
		{
			//child 1
			//close(STDIN_FILENO);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			ft_exec_cmd(env, tmp->next->next->cmd_to_exec);
		}
		else
		{pid = fork();
		if (pid < 0)
		{
			perror("c'est la D\n");
			return (-1);
		}
		if (pid == 0)
			pid2 = fork();
			if (pid2 < 0)
				return (-1);
			if (pid2 == 0)
			{
				//child2 (le premier exec)
				//close(STDOUT_FILENO);
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);	if (fd_0 != 0)
		dup2(fd_0, 0);
				close(fd[0]);
				close(fd[1]);
				
				//Ce qu'on veut utiliser pour ecrire dans le fichier
				//dup2(fd_file, STDIN_FILENO);
				//close(fd_file);
		}
		i++;
		tmp = tmp->next->next;
	}
	while (i < nb_cmd - 1)
	{
		i--;
		waitpid(pid1, &status, 0);
	}
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