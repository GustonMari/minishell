#include "../includes/function.h"

int	find_next_single_block(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE || str[i] == '$'/*  || str[i] == BACK_SLASH */)
			return (i);
		i++;
	}
	return (i);
}

char	*expand_node_single(char **env, char *str)
{
	int		i;
	char	*block;
	char	*expanded;
	int		not_expand;

	block = NULL;
	not_expand = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == D_QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == '$')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			if (str[i + 1] != '\0' && not_expand == 0)
				block = expand_single_dollar(env, block);
			not_expand = 0;
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			i++;
			block = cpy_block(&str[i], find_next_block(&str[i]));
			i += find_next_block(&str[i]);
		}
		else
		{
			block = cpy_block(&str[i], find_next_block(&str[i]));
			if (ft_find_d_chv_l_str(block, "<<", 2) == TRUE)
				not_expand = 1;
			i += find_next_single_block(&str[i]);
		}
		expanded = ft_strjoin_free(expanded, block, 1);
		free(block);
	}
	free(str);
	return (expanded);

}



/* t_token	*expand_single(char **env, t_token *all)
{
	t_token	*tmp;
	int		expand;

	expand = 1;
	tmp = all;
	while (tmp)
	{
		if (expand)
		{
			tmp = expand_node_single(env, tmp);
			if (!tmp->content)
				return (NULL);
		}
		expand = 1;
		if (tmp->type == D_CHV_L)
			expand = 0;
		tmp = tmp->next;
	}
	return (all);
} */