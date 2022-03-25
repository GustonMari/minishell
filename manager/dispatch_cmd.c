#include "../includes/function.h"

char	**ft_dispatch(t_command *all, t_token *expanded, char **env)
{
	t_command	*tmp;

	tmp = all;

	// a mettre ailleurs
	//if(check_cmd_list(tmp) == -1)
	//		return (env);
	
	if (count_cmd_list(tmp) == 1 && is_builtin(tmp->cmd_to_exec[0]))
		env = execute_one_cmd(env, all);
	else
		execute_pipe(tmp, expanded, env,  STDIN_FILENO);
	return (env);
}