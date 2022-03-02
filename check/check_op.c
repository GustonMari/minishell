#include "../includes/function.h"

int	is_operator_type(t_command *op)
{
	if (op->type == PIPE)
		return (1);
	if (op->type == CHV_L)
		return (1);
	if (op->type == D_CHV_L)
		return (1);
	if (op->type == CHV_R)
		return (1);
	if (op->type == D_CHV_R)
		return (1);
	return (0);
}

int	check_cmd_list(t_command *all)
{
	t_command *tmp;

	tmp = all;
	if (is_operator_type(tmp))
		return (-1);
	while (tmp->next)
	{
		if (is_operator_type(tmp))
		{
			if (is_operator_type(tmp->next))
			{
				ft_print_error(1, NULL, "syntax error near unexpected token ", tmp->cmd_to_exec[0]);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	if (is_operator_type(tmp))
		return (-1);
	return (0);
}