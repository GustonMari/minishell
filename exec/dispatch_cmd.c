#include "../includes/function.h"



/* int ft_count_cmd(t_command *all)
{

} */

int ft_dispatch(t_command *all, char **env)
{
    t_command *tmp;

    tmp = all;
    execute_pipe(tmp, env, 2);
    /* ft_exec_cmd(env, tmp->cmd_to_exec); */
    return (0);
}