#include "../includes/function.h"


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

int	last_quote(char *arg)
{
	int	i;
	int	place;

	place = 1;
	i = 1;
	while (arg[i] && !is_operator(&arg[i]))
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			place = i;
		i++;
	}
	return (place);
}

int	create_word(char *arg, t_token **begin)
{
	int		i;
	int		place;
	char	*word;

	i = 0;
	if (((arg[i] == '\"') || (arg[i] == '\'')))
	{
		place = last_quote(arg);
		while (arg[i] && i <= place)
			i++;
	}
	else
	{
		while (arg[i] && !is_operator(&arg[i]) && !ft_is_space(arg[i]))
			i++;
	}
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
	if (check_quote(arg))
		return (NULL);
	while(arg[i])
	{
		op = is_operator(&arg[i]);
		if (op)
			i += create_op(&begin, op);
		else if (!op && (arg[i] != ' '))
			i += create_word(&arg[i], &begin);
		else if (ft_is_space(arg[i]))
			i++;
	}
	free(arg);
	return (begin);
}

/* int main()
{
	char	enter[] = "echo\"salut\" | \"ouiii \'ouii\" ";
	// char	enter[] = "hey \"ta grande daronne sa\" mere | ca > < lol"; 
	t_token	*begin = NULL;
	(void)begin;

	begin = lexer(enter);
	print_token(&begin);
	ft_lstclear(&begin, free);
} */
