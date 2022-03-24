#include "../includes/function.h"

/* Count le nombre de redirections gauche qu'il y a entre deux pipe*/

int	count_redir_l(t_command *all_cmd)
{
	t_command	*tmp;
	int			nb_redir;

	nb_redir = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_L || tmp->type == D_CHV_L)
			nb_redir++;
		tmp = tmp->next;
	}
	return (nb_redir);
}

/* Trouve la derniere redirection gauche
et renvoi le nom du fichier correspondant a la derniere redirection
(cmd plutot ?)*/

char	*find_last_redir_l(t_command *all_cmd)
{
	t_command	*tmp;
	char		*file_name;
	int			is_redir_l;

	is_redir_l = 0;
	file_name = NULL;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_L)
			is_redir_l = 1;
		if (tmp->type == WORD && is_redir_l == 1)
		{
			free(file_name);
			file_name = ft_strdup(tmp->cmd_to_exec[0]);
			if (!file_name)
				return (NULL);
			is_redir_l = 0;
		}
		tmp = tmp->next;
	}
	//if (!priorities_D_CHV_L(all_cmd))
	//	return (ft_strdup(".heredoc"));
	return (file_name);
}

int	manage_single_chv_l(t_command *all_cmd)
{
	if (all_cmd->type == CHV_L)
	{
		if (all_cmd->next && (access((all_cmd->next->cmd_to_exec[0]), F_OK | R_OK) < 0))
		{
			ft_putstr_fd(BRED"minishell: ", 2);
			ft_putstr_fd(all_cmd->next->cmd_to_exec[0], 2);
			ft_putstr_fd(BRED": No such file or directory\n"CRESET, 2);
			return (-1);
		}
	}
	return (0);
}

int	manage_chv_l(t_command *all_cmd, char **env)
{
	char		*file_name;
	int			fd;
	(void)env;

	file_name = NULL;
	g_status = 0;
	if (count_redir_l(all_cmd) == 0)
		return (1);
	file_name = find_last_redir_l(all_cmd);
	if (!file_name)
		return (-1);
	if (manage_single_chv_l(all_cmd) < 0)
		return (-2);
	//if (count_nb_D_CHV_L_between_pipe(all_cmd) != 0)
	//	launch_heredoc(all_cmd, env);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		fd = open(".tmp", O_RDONLY, 00777);
		dup2(fd, 1);
		close(fd);
		redirection_error(file_name);
		return (-2);
	}
	dup2(fd, 0);
	close(fd);
	free(file_name);
	return (0);
}