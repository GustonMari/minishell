#include "../includes/function.h"

int	erase_file(t_command *all_cmd, char *file_error)
{
	t_command	*tmp;
	int			fd;
	t_command	*previous;

	tmp = all_cmd;
	previous = tmp;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE && ft_strcmp(tmp->cmd_to_exec[0], file_error))
	{
		if (tmp->type == WORD && (previous->type == CHV_R || previous->type == D_CHV_R))
		{
			fd = open(tmp->cmd_to_exec[0], O_TRUNC);
			close(fd);
		}
		else 
			previous = tmp;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && (previous->type == CHV_R || previous->type == D_CHV_R))
		{
			unlink(tmp->cmd_to_exec[0]);
		}
		else 
			previous = tmp;
		tmp = tmp->next;
	}
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

int	redirection_clean(t_command *all_cmd)
{
	t_command	*tmp;
	char		*file_error;
	t_command	*previous;

	if (count_redir(all_cmd) == 0)
		return (0);
	tmp = all_cmd;
	previous = tmp;
	if (tmp->next)
		tmp = tmp->next;
	else
		return (0);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			if ((access((tmp->cmd_to_exec[0]), F_OK | R_OK) < 0 && previous->type == CHV_L)
				|| (access((tmp->cmd_to_exec[0]), R_OK) < 0 && (previous->type == CHV_R
					|| previous->type == D_CHV_R)))
			{
				file_error = ft_strdup((tmp->cmd_to_exec[0]));
				if (!file_error)
					return (-1);
				//fprintf(stderr, "file_error = %s\n", file_error);
				//erase_file(all_cmd, file_error);
				return (1);
			}
		}
		else
			previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	redirection_manager(t_command *all_cmd)
{

	if (manage_chv_l(all_cmd) == -1)
		return (FALSE);
	if (manage_chv_r(all_cmd) == -1)
		return (FALSE);
	return (TRUE);
}