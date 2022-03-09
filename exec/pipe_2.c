#include "../includes/function.h"

int count_all_between_pipe(t_command **all_cmd)
{
	while (*all_cmd && (*all_cmd)->type != PIPE)
		*all_cmd = (*all_cmd)->next;
	if (*all_cmd)
		*all_cmd = (*all_cmd)->next;
	return (0);
}