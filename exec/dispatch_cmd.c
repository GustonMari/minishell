#include "../includes/function.h"



/* int ft_count_cmd(t_command *all)
{

} */

int	ft_dispatch(t_command *all, char **env)
{
	t_command	*tmp;

	tmp = all;
	if(check_cmd_list(tmp) == -1)
			return (-1);
	if (count_cmd_list(tmp) == 1 && is_builtin(tmp->cmd_to_exec[0]))
		env = execute_one_cmd(env, all);
	else
		execute_pipe(tmp, env, count_cmd_list(tmp));
	//ft_exec_cmd(env, tmp->cmd_to_exec);
	return (0);
}