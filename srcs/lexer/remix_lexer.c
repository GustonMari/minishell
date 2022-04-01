#include "../includes/function.h"

/*
	check la taille si lon commence par un < jusqua a la fin de la liste ou au prochain op
*/

int	remix_size_three(t_token *lst)
{
	if (lst->next)
		lst = lst->next;
	if (token_is_redir(lst) && count_word_btw_two_op(lst) == 1)
		return (1);
	else
		return (0);
}

/*
	fonction de push_swap intervertit 1 et 2
*/
void	ft_sa(t_token **head)
{
	t_token	*temp;
	t_token	*forward;

	temp = *head;
	forward = temp;
	forward = forward->next;
	temp->next = forward->next;
	forward->next = temp;
	*head = forward;
}

/*
	on cherche ici a resoudre le cas suivant wc < ok -l < salut  <=> wc -l < ok < salut . la regle consiste asi on rencontre un chevron
	gauche et ensuite deux mots (ou plus), decaler le chevron et le premier mots tt a la droite jusquau moment ou 
	lon trouvera un operateur quelconque. Exemple:
	<ok wc -l < salut <=> wc -l < ok < salut
*/


void	remix_lexer(t_token **all)
{

	t_token	*tmp;
	t_token	*before_chv_l;

	tmp = *all;
	if (token_is_redir(tmp) && (count_word_btw_two_op(tmp) > 1))
	{
		mv_word_left(tmp);
		ft_sa(&tmp);
		if (!remix_size_three(tmp))
			mv_chv_l(tmp);
		*all = tmp;
		return ;
	}
	before_chv_l = *all;
	while (tmp)
	{
		if (token_is_redir(tmp))
		{
				if (count_word_btw_two_op(tmp) > 1)
				{
					mv_word_left(tmp);
					mv_chv_l(before_chv_l);
					while (tmp && !token_is_operator(tmp))
						tmp = tmp->next;
				}
		}
		before_chv_l = tmp;
		tmp = tmp->next;
	}
}

int	ft_need_remix(t_token **all)
{
	t_token *tmp;

	tmp = *all;
	while(tmp)
	{
		if (token_is_redir(tmp))
		{
				if (count_word_btw_two_op(tmp) > 1)
					return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
	manage le remix 
*/

void	remix_manager(t_token **all)
{
	if (ft_need_remix(all) == 0)
		return ;
	else
	{
		while (ft_need_remix(all) == 1)
			remix_lexer(all);
	}
}


/* int	g_status;

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_token *temp = NULL;
	//t_token	*expanded = NULL;
	//t_command *cmd_all = NULL;
	//cmd_all = NULL;
    char **env = NULL;
	char *line = NULL;

	env = ft_create_env(envp);
	line = ft_strdup("<< ok wc < yes -c | < ok cat");
	temp = lexer(line);
	//mv_word_left(temp);
	printf("------- BEFORE -----------\n");
	print_token(&temp);
	printf("------------------\n");
	
	//remix_lexer(&temp);
	//remix_lexer(&temp);
	//remix_lexer(&temp);
	remix_manager(&temp);

	printf("------- AFTER -----------\n");
	print_token(&temp);
	printf("------------------\n");
	//ft_lstclear(&expanded, free);
	//ft_cmd_clear(&cmd_all);
	ft_free_tab_2d(env);
    return (0);
} */