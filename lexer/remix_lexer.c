#include "../includes/function.h"

/*
	check la taille si lon commence par un < jusqua a la fin de la liste ou au prochain op
*/

int	remix_size_three(t_token *lst)
{
	// int	i;

	// i = 1;
	if (lst->next)
		lst = lst->next;
	if (lst->type == CHV_L && count_word_btw_two_op(lst) ==1)
		return (1);
	else
		return (0);
	/* while (lst && lst->type != CHV_L)
	{
		lst = lst->next;
		i++;
	}
	return (i); */
}

/*
	fonction de push_swap intervertit 1 et 2
*/
void	ft_sa(t_token **head)
{
	t_token	*temp;
	t_token	*forward;

	//if (!*head || ft_lstsize(*head) == 1)
	//	return ;
	temp = *head;
	forward = temp;
	forward = forward->next;
	temp->next = forward->next;
	forward->next = temp;
	*head = forward;
	//ft_addback_operation(head_op, ft_create_new_operation("sa"));
}

/*
	on cherche ici a resoudre le cas suivant wc < ok -l < salut  <=> wc -l < ok < salut . la regle consiste asi on rencontre un chevron
	gauche et ensuite deux mots (ou plus), decaler le chevron et le premier mots tt a la droite jusquau moment ou 
	lon trouvera un operateur quelconque. Exemple:
	<ok wc -l < salut <=> wc -l < ok < salut
*/


void	remix_lexer(t_token **all)
{

	//t_token	*tmp;
	t_token	*before_chv_l;

	//tmp = *all;
	//function si < en premier position de cmd_line
	if (tmp->type == CHV_L && (count_word_btw_two_op(tmp) > 1))
	{
		//ft_sa(&tmp);
		mv_word_left(tmp);
		ft_sa(&tmp);
		if (!remix_size_three(tmp))
			mv_chv_l(tmp);
		*all = tmp;
		return ;
	}
	// printf("------- AFTER rmeix -----------\n");
	// print_token(all);
	// printf("------------------\n");
	before_chv_l = *all;
	while (tmp)
	{
		if (tmp->type == CHV_L)
		{
				if (count_word_btw_two_op(tmp) > 1)
				{
					//printf("NOOOON");
					mv_word_left(tmp);
					mv_chv_l(before_chv_l);
					//tmp = mv_redir_left(before_chv_l);
					// on se retrouve apres substitution au noed avant lancienne position de chvr_l
					while (tmp && tmp->type != CHV_L)
						tmp = tmp->next;
				}
		}
		before_chv_l = tmp;
		tmp = tmp->next;
	}
	//tmp = *all;
	// printf("------- AFTER rmeix -----------\n");
	// print_token(all);
	// printf("------------------\n");
}

int	ft_need_remix(t_token **all)
{
	t_token *tmp;

	tmp = *all;
	while(tmp)
	{
		if (tmp->type == CHV_L)
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

void	remix_manager(t_token *all)
{
	//t_token *tmp;

	//tmp = all;
	if (ft_need_remix(&all) == 0)
		return ;
	else
	{
		while (ft_need_remix(&all) == 1)
			remix_lexer(&all);
	}
}


int	g_status;

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
	line = ft_strdup("< ok wc -l < yes -c");
	temp = lexer(line);
	//mv_word_left(temp);
	printf("------- BEFORE -----------\n");
	print_token(&temp);
	printf("------------------\n");
	
	//remix_lexer(&temp);
	 //remix_lexer(&temp);
	//remix_lexer(&temp);
	remix_manager(temp);

	printf("------- AFTER -----------\n");
	print_token(&temp);
	printf("------------------\n");
	//ft_lstclear(&expanded, free);
	//ft_cmd_clear(&cmd_all);
	ft_free_tab_2d(env);
    return (0);
}