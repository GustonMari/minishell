#include "../includes/function.h"

char	**manage_line(char **env, char *line)
{
	t_token		*temp;
	t_token		*expanded;
	t_command	*cmd_all;
	(void)cmd_all;

	temp = lexer(line);
	expanded = expand_all(env, temp);
	//REMOVE
	//print_token(&expanded);
	trim_all(&expanded);
	//REMOVE
	//print_token(&expanded);
	cmd_all = token_to_cmd(expanded);
	env = ft_dispatch(cmd_all, env);
	//print_cmd(&cmd_all);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	return (env);
}
