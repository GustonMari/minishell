#include "../includes/function.h"

int	redirection_manager(t_command *all_cmd)
{

	if (manage_chv_l(all_cmd) == -1)
		return (FALSE);
	if (manage_chv_r(all_cmd) == -1)
		return (FALSE);
	return (TRUE);
}