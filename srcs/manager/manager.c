#include "../includes/function.h"

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
	if(check_cmd_list(tmp) < 0)
	{
		ft_lstclear(&tmp, free);
		free(clean);
		return (env);
	}
	expanded = expand_all(env, tmp, clean);
	clean->token_begin = expanded;
	cmd_all = token_to_cmd(expanded);
	clean->command_begin = cmd_all;
	if (manage_heredoc(&cmd_all, env, clean) < 0)
	{
		delete_heredoc_file(cmd_all);
		ft_lstclear(&expanded, free);
		ft_cmd_clear(&cmd_all);
		free(clean);
		return (env);
	}
	remix_2(&cmd_all);
	// clean = malloc(sizeof(clean) * 3);
	// clean->token_begin = expanded;
	// clean->command_begin = cmd_all;
	// clean->env = env;
	env = ft_dispatch(cmd_all, clean, env);
	if (delete_heredoc_file(cmd_all) < 0)
	{
		//On doit exit, erreur malloc
		return (env);
	}
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	free(clean);
	return (env);
}
