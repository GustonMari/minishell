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

	ATTENTION NE MARCHE PAS ENCORE POUR LE CAS < ok wc
*/

void	mv_word_left(t_token *all)
{

	t_token	*tmp = NULL;
	t_token	*forward = NULL;
	t_token	*word = NULL;

	//all serra ici toujours "<"
	tmp = all;
	//foward pointe sur -l
	forward = tmp->next->next;
	// word sur ok
	word = tmp->next;
	// tmp est sur le chevron et on veut link le chevron et le WORD + 1 ex: < ok -l on link < et -l
	//if (tmp->type != CHV_L)
	// tmp = tmp->next;
	// on link le chv_l et -l
	tmp->next = forward;
	//if (tmp-> type != CHV_L)
	//if (tmp->next->next->type != CHV_L)
	tmp = tmp->next;
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
		tmp = tmp->next;
	}
}

/*
	deplace chv_l avant le mot
*/

void	mv_chv_l(t_token *all)
{

	t_token	*tmp = NULL;
	t_token	*forward = NULL;
	t_token	*word = NULL;

	//all serra ici toujours le noead avant chv_l
	tmp = all;
	//foward pointe sur -l
	forward = tmp->next->next;
	// word sur ok
	word = tmp->next;
	// tmp est sur le chevron et on veut link le chevron et le WORD + 1 ex: < ok -l on link < et -l
	//if (tmp->type != CHV_L)
	// tmp = tmp->next;
	// on link le chv_l et -l
	tmp->next = forward;
	//if (tmp-> type != CHV_L)
	tmp = tmp->next;
	while (tmp /* && !token_is_operator(tmp) */)
	{
		if ((tmp->next->next == NULL) || (token_is_operator(tmp->next->next)))
		{
			if (tmp->next)
				word->next = tmp->next;
			else
				word->next = NULL;
			tmp->next = word;
			break ;
		}
		tmp = tmp->next;
	}
}
