/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:26:09 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 13:22:41 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	manage_check_quote(char *line, t_to_clean *clean)
{
	if (check_quote(line) == FALSE)
	{
		ft_putstr_fd(BRED"minishell: you should close quote\n"CRESET, 2);
		free(clean);
		free(line);
		return (FALSE);
	}
	return (TRUE);
}

int	manage_check_cmd_list(t_token *tmp, t_to_clean *clean)
{
	if (check_cmd_list(tmp) < 0)
	{
		ft_lstclear(&tmp, free);
		free(clean);
		return (FALSE);
	}
	return (TRUE);
}

int	manage_heredoc_main(t_command *cmd_all,
	t_to_clean *clean, t_token *expanded)
{
	if (manage_heredoc(&cmd_all, clean) < 0)
	{
		delete_heredoc_file(cmd_all);
		ft_lstclear(&expanded, free);
		ft_cmd_clear(&cmd_all);
		free(clean);
		return (FALSE);
	}
	return (TRUE);
}

void	manage_line_clean(t_to_clean *clean,
	t_command *cmd_all, t_token *expanded)
{
	if (delete_heredoc_file(cmd_all) < 0)
		ft_clean_error_malloc(clean);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	free(clean);
}

char	**manage_line(char **env, char *line)
{
	t_token		*tmp;
	t_token		*expanded;
	t_command	*cmd_all;
	t_to_clean	*clean;

	cmd_all = NULL;
	tmp = NULL;
	clean = NULL;
	clean = clean_init(clean, env, line);
	if (manage_check_quote(line, clean) == FALSE)
		return (env);
	line = expand_node_single(clean, env, line);
	tmp = lexer(clean, line);
	if (!tmp)
		return (env);
	remix_manager(&tmp);
	if (manage_check_cmd_list(tmp, clean) == FALSE)
		return (env);
	expanded = expand_all(env, tmp, clean);
	clean->token_begin = expanded;
	cmd_all = token_to_cmd(expanded, clean);
	clean->command_begin = cmd_all;
	if (manage_heredoc(&cmd_all, clean) == FALSE)
		return (env);
	remix_2(&cmd_all);
	env = ft_dispatch(cmd_all, clean, env);
	manage_line_clean(clean, cmd_all, expanded);
	return (env);
}
