#include "../includes/function.h"

char	*exit_expand_node_single(t_to_clean *clean, char **env, char *str, char *expanded)
{
	free(str);
	free(expanded);
	ft_free_tab_2d(env);
	free(clean);
	exit(errno);
	return (NULL);
}

void	*ft_clean_error_malloc(t_to_clean *clean)
{
	if (clean->token_begin)
		ft_lstclear(&(clean->token_begin), free);
	if (clean->command_begin)
		ft_cmd_clear(&(clean->command_begin));
	if (clean->env)
		ft_free_tab_2d(clean->env);
	if (clean)
		free(clean);
	rl_clear_history();
	exit(errno);
	return (NULL);
}
