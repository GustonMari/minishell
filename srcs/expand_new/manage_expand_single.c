#include "../includes/function.h"

int	find_next_single_block(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*expand_node_single(t_to_clean *clean, char **env, char *str)
{
	int		i;
	char	*block;
	char	*expanded;
	int		not_expand;

	block = NULL;
	not_expand = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (exit_expand_node_single(clean, env, str, expanded));
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			if (!block)
				return (exit_expand_node_single(clean, env, str, expanded));
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == D_QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			if (!block)
				return (exit_expand_node_single(clean, env, str, expanded));
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == '$')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			if (!block)
				return (exit_expand_node_single(clean, env, str, expanded));
			//WARNING EXPANDED DANS EXPAND SINGLE DOLLARS
			if (str[i + 1] != '\0' && not_expand == 0 && !ft_is_space(str[i + 1]))
				block = expand_single_dollar(env, block, clean);
			not_expand = 0;
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			i++;
			block = cpy_block(&str[i], find_next_block(&str[i]), clean);
			if (!block)
				return (exit_expand_node_single(clean, env, str, expanded));
			i += find_next_block(&str[i]);
		}
		else
		{
			block = cpy_block(&str[i], find_next_block(&str[i]), clean);
			if (!block)
				return (exit_expand_node_single(clean, env, str, expanded));
			if (ft_find_d_chv_l_str(block, "<<", 2) == TRUE)
				not_expand = 1;
			i += find_next_single_block(&str[i]);
		}
		expanded = ft_strjoin_free(expanded, block, 1);
		if (!expanded)
		{
			free(block);
			return (exit_expand_node_single(clean, env, str, expanded));
		}
		free(block);
	}
	free(str);
	return (expanded);
}
