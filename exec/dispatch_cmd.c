#include "../includes/function.h"

char	**ft_dispatch(t_command *all, char **env)
{
	t_command	*tmp;

	tmp = all;
	if(check_cmd_list(tmp) == -1)
			return (env);
	if (count_cmd_list(tmp) == 1 && is_builtin(tmp->cmd_to_exec[0]))
		env = execute_one_cmd(env, all);
	else
	{
		// refaire grande boucle pour avoir toute les cmd en different pipe
		execute_pipe(tmp, env, count_cmd_between_pipe(tmp));
	}
	//ft_redirection_chv_r("pouetpouetpizza");
	//ft_exec_cmd(env, tmp->cmd_to_exec);
	return (env);
}