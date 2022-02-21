#include "../function.h"


int	create_op(t_token **begin, int op)
{
	if (op == PIPE)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("|"), PIPE));
		return (1);
	}
	else if (op == CHV_R)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup(">"), CHV_R));
		return (1);
	}
	else if (op == CHV_L)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("<"), CHV_L));
		return (1);
	}
	else if (op == D_CHV_R)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup(">>"), D_CHV_R));
		return (2);
	}
	else if (op == D_CHV_L)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("|"), D_CHV_L));
		return (2);
	}
	return (0);
}

int	define_operator(char *operator)
{
	if (!ft_strncmp("|", operator, 1))
		return (PIPE);
	if (!ft_strncmp(">", operator, 1))
		return (CHV_R);
	if (!ft_strncmp("<", operator, 1))
		return (CHV_L);
	if (!ft_strncmp(">>", operator, 2))
		return (D_CHV_R);
	if (!ft_strncmp("<<", operator, 2))
		return (D_CHV_L);
	return (0);
}

char	*cpy_word(char *arg, int end)
{
	char	*to_cpy;
	char	*word;

	to_cpy = ft_strdup(arg);
	if (!to_cpy)
		return (NULL);
	to_cpy[end] = '\0';
	word = ft_strdup(to_cpy);
	if (!word)
		return (NULL);
	free(to_cpy);
	return (word);
}



int	create_word(char *arg, t_token **begin)
{
	int	i;
	char	*word;

	i = 0;
	while (arg[i] && !define_operator(&arg[i]) && !ft_is_space(arg[i]))
		i++;
	word = cpy_word(arg, i);
	ft_lstadd_back(begin, ft_lstnew(word, WORD));
	return (i);
}

t_token	*lexer(char *arg)
{
	t_token	*begin = NULL;
	int	i;
	int	op;

	i = 0;
	//if (check_quote)
	//	return (NULL);
	while(arg[i])
	{
		op = define_operator(&arg[i]);
		if (op)
			i += create_op(&begin, op);
		else if (!op && (arg[i] != ' '))
			i += create_word(&arg[i], &begin);
		else if (ft_is_space(arg[i]))
			i++;
	}
	return (begin);
}

/* int main()
{
	char	enter[] = "hey \"ta grande daronne sa\" mere | ca > < lol";
	t_token	*begin = NULL;
	(void)begin;

	begin = lexer(enter);
	print_token(&begin);
	ft_lstclear(&begin, free);
	//print_token(&begin);
}
 */