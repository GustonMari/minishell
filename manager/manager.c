#include "../includes/function.h"

char	**manage_line(char **env, char *line)
{
	t_token		*temp;
	t_token		*expanded;
	t_command	*cmd_all;
	(void)cmd_all;

	temp = lexer(line);
	if (!temp)
		return (env);
	expanded = expand_all(env, temp);
	cmd_all = token_to_cmd(expanded);
	env = ft_dispatch(cmd_all, env);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	return (env);
}
