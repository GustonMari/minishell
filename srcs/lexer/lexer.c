#include "../includes/function.h"

int	create_op(t_token **begin, int op, t_to_clean *clean)
{
	if (op == PIPE)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("|"), PIPE, clean));
		return (1);
	}
	else if (op == CHV_R)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup(">"), CHV_R, clean));
		return (1);
	}
	else if (op == CHV_L)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("<"), CHV_L, clean));
		return (1);
	}
	else if (op == D_CHV_R)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup(">>"), D_CHV_R, clean));
		return (2);
	}
	else if (op == D_CHV_L)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("<<"), D_CHV_L, clean));
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

int	create_word(char *arg, t_token **begin, t_to_clean *clean)
{
	int		i;
	char	*word;

	i = 0;
	while (arg[i] && !is_operator(&arg[i]) && !ft_is_space(arg[i]))
	{
		if (((arg[i] == '\"') || (arg[i] == '\'')))
			i += find_next_quote(&arg[i]);
		else
			i++;
	}
	word = cpy_word(arg, i);
	ft_lstadd_back(begin, ft_lstnew(word, WORD, clean));
	return (i);
}

/* int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
} */

t_token	*lexer(t_to_clean *clean, char *arg)
{
	t_token	*begin;
	int		i;
	int		op;

	i = 0;
	begin = NULL;
	if (check_quote(arg))
	{
		ft_putstr_fd(BRED"minishell: you should close quote\n"CRESET, 2);
		g_status = 1;
		return (NULL);
	}
	while (arg[i])
	{
		op = is_operator(&arg[i]);
		if (op)
			i += create_op(&begin, op, clean);
		else if (!op && (!ft_is_space(arg[i])))
			i += create_word(&arg[i], &begin, clean);
		else if (ft_is_space(arg[i]))
			i++;
	}
	free(arg);
	return (begin);
}

