/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:17:23 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 23:32:18 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	**manage_line_bis_4(char **env, t_token *expanded,
	t_command *cmd_all, t_to_clean *clean)
{
	delete_heredoc_file(cmd_all);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	free(clean);
	return (env);
}

char	**manage_line_bis_3(char **env, t_token *tmp, t_to_clean *clean)
{
	ft_lstclear(&tmp, free);
	free(clean);
	return (env);
}

char	**manage_line_bis_2(char **env, char *line, t_to_clean *clean)
{
	ft_putstr_fd(BRED"minishell: you should close quote\n"CRESET, 2);
	free(clean);
	free(line);
	return (env);
}

char	**manage_line_bis_1(char **env, char *line)
{
	free(line);
	if (env)
		ft_free_tab_2d(env);
	exit(errno);
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
	clean = malloc(sizeof(clean) * 4);
	if (!clean)
		return (manage_line_bis_1(env, line));
	clean->env = env;
	clean->token_begin = NULL;
	clean->command_begin = NULL;
	if (check_quote(line) == FALSE)
		return (manage_line_bis_2(env, line, clean));
	line = expand_node_single(clean, env, line);
	tmp = lexer(clean, line);
	if (!tmp)
		return (env);
	remix_manager(&tmp);
	if (check_cmd_list(tmp) < 0)
		return (manage_line_bis_3(env, tmp, clean));
	expanded = expand_all(env, tmp, clean);
	clean->token_begin = expanded;
	cmd_all = token_to_cmd(expanded, clean);
	clean->command_begin = cmd_all;
	if (manage_heredoc(&cmd_all, clean) < 0)
		return (manage_line_bis_4(env, expanded, cmd_all, clean));
	remix_2(&cmd_all);
	env = ft_dispatch(cmd_all, clean, env);
	if (delete_heredoc_file(cmd_all) < 0)
		ft_clean_error_malloc(clean);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	free(clean);
	return (env);
}

/* char	**manage_line(char **env, char *line)
{
	t_token		*tmp;
	t_token		*expanded;
	t_command	*cmd_all;
	t_to_clean	*clean;

	cmd_all = NULL;
	tmp = NULL;
	clean = NULL;
	clean = malloc(sizeof(clean) * 4);
	if (!clean)
	{
		free(line);
		free(clean);
		exit(errno);
	}
	clean->env = env;
	clean->token_begin = NULL;
	clean->command_begin = NULL;
	if (check_quote(line) == FALSE)
	{
		ft_putstr_fd(BRED"minishell: you should close quote\n"CRESET, 2);
		free(clean);
		free(line);
		return (env);
	}
	line = expand_node_single(clean, env, line);
	tmp = lexer(clean, line);
	if (!tmp)
		return (env);
	remix_manager(&tmp);
	if (check_cmd_list(tmp) < 0)
	{
		ft_lstclear(&tmp, free);
		free(clean);
		return (env);
	}
	expanded = expand_all(env, tmp, clean);
	clean->token_begin = expanded;
	cmd_all = token_to_cmd(expanded, clean);
	clean->command_begin = cmd_all;
	if (manage_heredoc(&cmd_all, clean) < 0)
	{
		delete_heredoc_file(cmd_all);
		ft_lstclear(&expanded, free);
		ft_cmd_clear(&cmd_all);
		free(clean);
		return (env);
	}
	remix_2(&cmd_all);
	env = ft_dispatch(cmd_all, clean, env);
	if (delete_heredoc_file(cmd_all) < 0)
		ft_clean_error_malloc(clean);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	free(clean);
	return (env);
} */