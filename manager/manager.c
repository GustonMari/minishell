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
	line = expand_node_single(env, line);
	tmp = lexer(line);
	if (!tmp)
		return (env);
	remix_manager(&tmp);
	if(check_cmd_list(tmp) < 0)
	{
		ft_lstclear(&tmp, free);
		return (env);
	}
	/* printf("------------------\n");
	print_token(&tmp);
	printf("------------------\n"); */
	expanded = expand_all(env, tmp);
	/* printf("AFTER------------------\n");
	print_token(&tmp);
	printf("------------------\n"); */
	cmd_all = token_to_cmd(expanded);
	if (manage_heredoc(&cmd_all, env) < 0)
	{
		//On doit exit, erreur malloc
		delete_heredoc_file(cmd_all);
		return (env);
	}
	/* printf("AFTER------------------\n");
	print_cmd(&cmd_all);
	printf("------------------\n"); */
	clean = malloc(sizeof(clean) * 3);
	clean->token_begin = expanded;
	clean->command_begin = cmd_all;
	clean->env = env;
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
