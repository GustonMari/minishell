#include "../includes/function.h"

int manage_line(char **env, char *line)
{
    t_token *temp;
	t_token	*expanded;
	t_command *cmd_all;
	(void)cmd_all;

	temp = lexer(line);
	expanded = expand_all(env, temp);
	trim_all(&expanded);
	cmd_all = token_to_cmd(expanded);
    ft_dispatch(cmd_all, env);
	//print_cmd(&cmd_all);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
    return (0);
}
