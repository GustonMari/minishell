#include "../includes/function.h"

int ft_dispatch(t_command *all, char **env)
{
    t_command *tmp;

    tmp = all;
    ft_exec_cmd(env, tmp->cmd_to_exec);
    return (0);
}