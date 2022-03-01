
#include "../includes/function.h"


int execute_pipe(t_command *all_cmd, char **env, int nb_cmd)
{
    int         i;
    int         fd[2];
    pid_t       pid1;
    pid_t       pid2;
    int         status;
    t_command   *tmp;
    int fd_file; 

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
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                ft_exec_cmd(env, tmp->next->next->cmd_to_exec);
        }
        else
        {
            pid2 = fork();
            if (pid2 < 0)
                return (-1);
            if (pid2 == 0)
            {
                //child2 (le premier exec)
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                ft_exec_cmd(env, tmp->cmd_to_exec);
            }
            else
            {
                close(fd[0]);
                close(fd[1]);
                waitpid(pid1, &status, 0);
                /*
                Ce qu'on veut utiliser pour ecrire dans le fichier
                dup2(fd_file, STDIN_FILENO);
                close(fd_file);*/
            }
        }
        i++;
        tmp = tmp->next->next;
    }
    return (0);
}


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
    char *line = ft_strdup("echo \"ouioiuoeooeu\" | wc");
	temp = lexer(line);
	expanded = expand_all(env, temp);
	trim_all(&expanded);
	cmd_all = token_to_cmd(expanded);
    execute_pipe(cmd_all, env, 2);
    //ft_dispatch(cmd_all, env);
	//print_cmd(&cmd_all);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
    return (0);
} */