#include "../includes/function.h"

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

int	count_redir_r(t_command *all_cmd)
{
	t_command	*tmp;
	int			nb_redir;

	nb_redir = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R || tmp->type == D_CHV_R)
			nb_redir++;
		tmp = tmp->next;
	}
	return (nb_redir);
}

int  manage_single_chv_r(t_command **all_cmd)
{
	int	fd;

	fd = -1;
	fprintf(stderr, "allllezz %s\n", (*all_cmd)->cmd_to_exec[0]);
	if ((*all_cmd)->type == CHV_R)
	{
		unlink((*all_cmd)->next->cmd_to_exec[0]);
		fd = open((*all_cmd)->next->cmd_to_exec[0], O_CREAT | O_TRUNC, 00644);
		if (fd < 0)
		{
			close(fd);
			return (-2);
		}
		if ((*all_cmd)->next && (*all_cmd)->next)
			(*all_cmd) = (*all_cmd)->next->next;
		//fprintf(stderr, "inside %s\n", (*all_cmd)->cmd_to_exec[0]);
		return (fd);
	}
	else if ((*all_cmd)->type == D_CHV_R)
	{
		fd = open((*all_cmd)->next->cmd_to_exec[0], O_CREAT | O_APPEND, 00644);
		if (fd < 0)
		{
			close(fd);
			return (-2);
		}

		if ((*all_cmd)->next && (*all_cmd)->next->next)
			(*all_cmd) = (*all_cmd)->next->next;
		return (fd);
	}
	return (-1);
}

int	manage_open_r(t_command *all_cmd, char *last_redir)
{
	t_command	*tmp;
	int			fd;

	fd = -1;
	fd = manage_single_chv_r(&all_cmd);
	if (fd != -1 || fd == -2)
		return (fd);
	fprintf(stderr, "zgegg \n");
	tmp = all_cmd;
	//fprintf(stderr, "begin last redir %s\n", last_redir);
	//fprintf(stderr, "tmp = %s\n", tmp->cmd_to_exec[0]);
	tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R)
		{
			fd = open(tmp->next->cmd_to_exec[0], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			if (fd < 0)
				return (-1);
		}
		else if (tmp->type == D_CHV_R)
		{
			fd = open(tmp->next->cmd_to_exec[0], O_CREAT | O_WRONLY | O_APPEND, 00644);
			if (fd < 0)
				return (-1);
		}
		if (tmp->next && !ft_strcmp(tmp->next->cmd_to_exec[0], last_redir))
			return (fd);
		if (tmp->next && tmp->next->next)
			tmp = tmp->next->next;
		else
			break ;
	}
	return (fd);
}

char	*find_last_redir_r(t_command *all_cmd)
{
	t_command	*tmp;
	char		*file_name;
	int			is_redir_r;

	is_redir_r = 0;
	file_name = NULL;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R || tmp->type == D_CHV_R)
			is_redir_r = 1;
		if (tmp->type == WORD && is_redir_r == 1)
		{
			free(file_name);
			file_name = ft_strdup(tmp->cmd_to_exec[0]);
			if (!file_name)
				return (NULL);
			is_redir_r = 0;
		}
		tmp = tmp->next;
	}
	return (file_name);
}

//faire gestion derreur

int	manage_chv_r(t_command *all_cmd)
{
	char		*file_name;
	int			fd;

	file_name = NULL;
	if (count_redir_r(all_cmd) == 0)
		return (1);
	file_name = find_last_redir_r(all_cmd);
	if (!file_name)
		return (-1);
	fd = manage_open_r(all_cmd, file_name);
	if (fd == -1)
	{
		dup2(fd, 1);
		close(fd);
		redirection_error(file_name);
		return (-2);
	}
	dup2(fd, 1);
	close(fd);
	free(file_name);
	return (0);
}
