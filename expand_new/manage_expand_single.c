#include "../includes/function.h"


char	*expand_node_single(char **env, char *str)
{
	int		i;
	char	*block;
	char	*expanded;
	(void)env;

	block = NULL;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			//block = trim_quote(block, &i);
			//block = add_echapment(block);
			//printf("block = %s\n", block);

			i += find_next_quote(&str[i]);
		}
		else if (str[i] == D_QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			//Trim nos double quote
			//block = trim_quote(block, &i);
			//printf("block D_QUOTE = %s\n", block);
			//Expand nos dollars dans notre block
			//block = expand_dollar(env, block);

			i += find_next_quote(&str[i]);
		}
		else if (str[i] == '$')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			if (str[i + 1] != '\0')
				block = expand_single_dollar(env, block);
			//printf("block DOLLAR = %s\n", block);
			i += find_next_quote(&str[i]);
			//Expand notre dollars
			//block = expand_dollar(env, block);
		}
		else
		{
			//join 1 par 1 (jusqu a ce qu on rencontre quote Dquote ou $, mais la 
			//boucle le fait tout seul)
			block = cpy_block(&str[i], find_next_block(&str[i]));
			i += find_next_block(&str[i]);
		}
		expanded = ft_strjoin_free(expanded, block, 1);
		free(block);
		//i++;

	}
	//ATTENTION LE FREE
	free(str);
	return (expanded);

}

/* t_token	*expand_node_single(char **env, t_token *all)
{
	int		i;
	char	*block;
	//char	*expanded;
	t_token	*tmp;

	tmp = all;
	block = NULL;
	//expanded = ft_strdup("");
	//if (!expanded)
	//	return (NULL);
	i = 0;
	while (tmp->content[i])
	{
		if (tmp->content[i] == QUOTE)
		{
			block = cpy_block(&tmp->content[i], find_next_quote(&tmp->content[i]));
			//block = trim_quote(block, &i);
			//block = add_echapment(block);
			//printf("block = %s\n", block);
		}
		else if (tmp->content[i] == D_QUOTE)
		{
			block = cpy_block(&tmp->content[i], find_next_quote(&tmp->content[i]));
			//Trim nos double quote
			//block = trim_quote(block, &i);
			//printf("block D_QUOTE = %s\n", block);
			//Expand nos dollars dans notre block
			//block = expand_dollar(env, block);
		}
		else if (tmp->content[i] == '$')
		{
			block = cpy_block(&tmp->content[i], find_next_quote(&tmp->content[i]));
			if (tmp->content[i + 1] != '\0')
				block = expand_single_dollar(env, block);
			//printf("block DOLLAR = %s\n", block);
			i += find_next_quote(&tmp->content[i]);
			//Expand notre dollars
			//block = expand_dollar(env, block);
		}
		else
		{
			//join 1 par 1 (jusqu a ce qu on rencontre quote Dquote ou $, mais la 
			//boucle le fait tout seul)
			block = cpy_block(&tmp->content[i], find_next_block(&tmp->content[i]));
			i += find_next_block(&tmp->content[i]);
		}

		//expanded = ft_strjoin_free(expanded, block, 1);
		free(block);
		//i++;

	}
	//free(str);
	return (all);

}

t_token	*expand_single(char **env, t_token *all)
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