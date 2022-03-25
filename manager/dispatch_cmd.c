#include "../includes/function.h"

char	**ft_dispatch(t_command *all, t_to_clean *clean, char **env)
{
	t_command	*tmp;

	tmp = all;

	if (count_cmd_list(tmp) == 1 && (is_builtin(tmp->cmd_to_exec[0])
		|| ft_strcmp(tmp->cmd_to_exec[0], "exit") == 0))
		env = execute_one_cmd(env, clean, all);
	else
		execute_pipe(tmp, clean, env,  STDIN_FILENO);
	return (env);
}