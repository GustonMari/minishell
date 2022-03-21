#include "../includes/function.h"

char	**manage_line(char **env, char *line)
{
	t_token		*tmp;
	t_token		*expanded;
	t_command	*cmd_all;
	(void)cmd_all;

	tmp = lexer(line);
	if (!tmp)
		return (env);
	//tmp = remix_lexer(tmp);
	/* printf("------------------\n");
	print_token(&tmp);
	printf("------------------\n"); */
	remix_manager(&tmp);
	/* printf("------------------\n");
	print_token(&tmp);
	printf("------------------\n"); */
	expanded = expand_all(env, tmp);
	/* printf("------------------\n");
	print_token(&expanded);
	printf("------------------\n"); */
	cmd_all = token_to_cmd(expanded);
	/* printf("AFTER------------------\n");
	print_cmd(&cmd_all);
	printf("------------------\n"); */
	env = ft_dispatch(cmd_all, env);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	return (env);
}
