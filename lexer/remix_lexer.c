#include "../includes/function.h"

/*
fonction qui permet de check si il y a plus dun mots apres un CHV_L et avant le prochain op
ex:
< ok wc -l < yes => ici on a trois WORD
*/

int	count_word_btw_two_op(t_token *all)
{
	t_token	*tmp;
	int		count;

	tmp = all;
	count = 0;
	//permet de zapper le chv_l
	tmp = tmp->next;
	while (tmp && !token_is_operator(tmp))
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

/*
	permet de bouger le mot apres le CHV_L
	on est dans le cas wc < ok -l
*/

void	mv_word_left(t_token *all)
{
	printf("------- BEFORE -----------\n");
	print_token(&all);
	printf("------------------\n");
	t_token	*tmp = NULL;
	t_token	*forward = NULL;
	t_token	*word = NULL;
	//t_token	*previous = NULL;
	//t_token	*next = NULL;
	//foward pointe sur -l
	tmp = all;
	forward = tmp->next->next->next;
	// word sur ok
	word = tmp->next->next;
		// tmp est sur le chevron et on veut link le chevron et le WORD + 1 ex: < ok -l on link < et -l
	tmp = tmp->next;
	//previous = tmp;
	// on link le chv_l et -l
	tmp->next = forward;
	tmp = tmp->next;
	printf(" .  %s\n", tmp->content);
	while (tmp /* && !token_is_operator(tmp) */)
	{
		if ((tmp->next == NULL) || (token_is_operator(tmp->next)))
		{
			
			if (tmp->next)
				word->next = tmp->next;
			else
				word->next = NULL;
			tmp->next = word;
			break ;
		}
		/* if (token_is_operator(tmp))
			break ; */
		//previous = tmp;
		//printf("previous %s\n", tmp->content);
		tmp = tmp->next;
		//printf("tmp %s\n", tmp->content);
		
	}
	printf("------- AFTER -----------\n");
	print_token(&all);
	printf("------------------\n");
}


/*
	cette fonction permet de bouger le CHV_L et le WORD suivant juste avant le prochain op ou fin de la cmd_line
	attwntion on se situe un noed avant
*/

/* void	mv_redir_left(t_token *all)
{
	t_token *tmp;

	tmp = all;

} */

/*
	on cherche ici a resoudre le cas suivant wc < ok -l < salut  <=> wc -l < ok < salut . la regle consiste asi on rencontre un chevron
	gauche et ensuite deux mots (ou plus), decaler le chevron et le premier mots tt a la droite jusquau moment ou 
	lon trouvera un operateur quelconque. Exemple:
	<ok wc -l < salut <=> wc -l < ok < salut
*/


/* t_token	*remix_lexer(t_token *all)
{
	t_token	*tmp;
	t_token	*before_chv_l;
	t_token	*actual;

	tmp = all;
	// faire function si < en premier position de cmd_line
	while (tmp)
	{
		if (tmp->type == CHV_L)
		{
				if (count_word_btw_two_op(tmp) > 1)
				{

					//tmp = mv_redir_left(before_chv_l);
					// on se retrouve apres substitution au noed avant lancienne position de chvr_l
				}
		}
		tmp = before_chv_l;
		tmp = tmp->next;
	}
} */

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
	line = ft_strdup("wc < ok -l -c < ls");
	temp = lexer(line);
	mv_word_left(temp);

	//ft_lstclear(&expanded, free);
	//ft_cmd_clear(&cmd_all);
	ft_free_tab_2d(env);
    return (0);
}