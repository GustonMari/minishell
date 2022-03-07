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

/* Va creer les fichiers apres les chevrons droits si ils n'existent pas 
et les effacer si ce n'est pas la derniere redirection droite (last_redir), retourne le 
fd du fichier dans lequel on va rediriger la cmd*/

int	manage_chv_r(t_command *all_cmd, char *last_redir)
{
	t_command	*tmp;
	int			is_chv_r;
	int			fd;

	is_chv_r = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R)
			is_chv_r = 1;
		if (tmp->type == WORD && is_chv_r == 1)
		{
			fd = open(tmp->cmd_to_exec[0], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			if (fd < 0)
				return (-1);
			//Inclure Errno
			close(fd);
			is_chv_r = 0;
		}
		tmp = tmp->next;
		if (!ft_strcmp(tmp->cmd_to_exec[0], last_redir))
			break ;
	}
	fd = open(tmp->cmd_to_exec[0], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0)
		return (-1);
	//Inclure Errno
	return (fd);
}

/* Trouve la derniere redirection en fonction de chv (on met droite ou gauche)
et renvoi le nom du fichier correspondant a la derniere redirection*/

char	*find_last_redir(t_command *all_cmd, t_tokentype chv_l)
{
	t_command	*tmp;
	char		*file_name;
	int			is_redir;

	is_redir = 0;
	file_name = NULL;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == chv_l)
			is_redir = 1;
		if (tmp->type == WORD && is_redir == 1)
		{
			free(file_name);
			file_name = ft_strdup(tmp->cmd_to_exec[0]);
			if (!file_name)
				return (NULL);
			is_redir = 0;
		}
		tmp = tmp->next;
	}
	return (file_name);
}

/* Retourne le fd_1, necessaire pour execute last, si il n'y a pas de 
redirection retourne STDOUT*/

/* int	redirection(t_command *all_cmd)
{
	t_command	*tmp;
	int			nb_redir;

	tmp = all_cmd;
	nb_redir = count_redir(tmp);
	if (tmp->next->next)
	{
		while (tmp && tmp->type != PIPE)
		{
			
		}
	}
	return (STDOUT_FILENO);
} */

int main(int ac, char **av, char **envp)
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
    char *line = ft_strdup("wc < lol > salut < sushi > moldu | > ok");
	temp = lexer(line);
	expanded = expand_all(env, temp);
	trim_all(&expanded);
	cmd_all = token_to_cmd(expanded);
    
	last_redir = find_last_redir(cmd_all, CHV_R);
	fd = manage_chv_r(cmd_all, last_redir);
	printf("last_redir = %s\n", last_redir);
	write(fd, "salut\n", 6);
	free(last_redir);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);

    return (0);
}