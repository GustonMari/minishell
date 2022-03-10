#include "../includes/function.h"

/* Retourne 1 si c'est une redir*/

int	is_redirection_type(t_command *op)
{
	if (op->type == CHV_L)
		return (1);
	if (op->type == D_CHV_L)
		return (1);
	if (op->type == CHV_R)
		return (1);
	if (op->type == D_CHV_R)
		return (1);
	return (0);
}

/* Count le nombre de redirection qu'il y a entre deux pipe*/

int	count_redir(t_command *all_cmd)
{
	t_command	*tmp;
	int			nb_redir;

	nb_redir = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redirection_type(tmp))
			nb_redir++;
		tmp = tmp->next;
	}
	return (nb_redir);
}

/* Retourne le out, necessaire pour execute last, si il n'y a pas de 
redirection retourne STDOUT*/

int	redirection(t_command *all_cmd, int *in, int *out, char **env)
{
	t_command	*tmp;
	int			nb_redir;

	tmp = all_cmd;
	nb_redir = count_redir(tmp);
	if (nb_redir < 1)
	{
		*out = STDOUT_FILENO;
		return (1);
	}
	if (manage_chv_l(all_cmd, in, env) == -1)
		return (-1);
	if (manage_chv_r(all_cmd, out) == -1)
		return (-1);
	if (*out == -1)
		return (-1);
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
	char	*last_redir;
	int		fd;
	(void)fd;

	env = ft_create_env(envp);
    char *line = ft_strdup("echo salut > prout >> nice > oui >> hahah");
	temp = lexer(line);
	expanded = expand_all(env, temp);
	trim_all(&expanded);
	cmd_all = token_to_cmd(expanded);
    
	last_redir = find_last_redir_r(cmd_all);
	fd = manage_open_r(cmd_all, last_redir);
	printf("last_redir = %s\n", last_redir);
	write(fd, "salut\n", 6);
	free(last_redir);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);

    return (0);
} */