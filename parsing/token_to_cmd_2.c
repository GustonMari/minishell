#include "../includes/function.h"

/* Transforme notre liste token en liste de cmd*/

t_command	*token_to_cmd(t_token *all)
{
	t_command	*cmd_all;
	t_token		*tmp_token;

	cmd_all = NULL;
	tmp_token = all;
	while (tmp_token)
	{	
		if (!is_operator(tmp_token->content))
			ft_add_back_cmd(&cmd_all, 
			create_new_cmd_node(token_to_tab(tmp_token), tmp_token));
		while (tmp_token && !is_operator(tmp_token->content))
			tmp_token = tmp_token->next;
		if (tmp_token && is_operator(tmp_token->content))
			ft_add_back_cmd(&cmd_all, 
			create_new_cmd_node(token_op_to_tab(tmp_token), tmp_token));
		if (tmp_token)
			tmp_token = tmp_token->next;
	}
	return (cmd_all);
}
