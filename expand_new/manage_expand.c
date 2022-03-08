#include "../includes/function.h"

char	*del_quote(char *str, int pos_a, int pos_b)
{
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	i = 0;
	j = 0;
	ret = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (i == pos_a && str[i])
			i++;
		if (i == pos_b && str[i])
		{
			i++;
			//ajout
			j++;
			break ;
		}
			
		ret[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	ret[j] = '\0';
	//free(str);
	return (ret);
}

char	*trim_quote(char *str, int *i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	if (str[k] == QUOTE || str[k] == D_QUOTE)
	{
		j = find_next_quote(str);
		str = del_quote(str, k, (j + k - 1));
		if (!str)
			return (NULL);
		
		*i += (j /* - 2 */);
	}
	return (str);
}

/*
		permet de copier une block, par exemple un block entre "" ou ''
*/

char	*cpy_block(char	*str, int size)
{
	char	*block;

	block = malloc(sizeof(char) * (size + 1));
	if (!block)
		return (NULL);
	block = ft_strncpy(block, str, (unsigned int)size);
	return (block);
}

/*Trouve le prochain block qui commence par un $ ou Quote ou DQuote ou se termine par '\0'
et renvoie sa position*/

int	find_next_block(char *str)
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

/*Expand un maillon */

char	*expand_node(char **env, char *str)
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
			block = trim_quote(block, &i);
		}
		else if (str[i] == D_QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			//Trim nos double quote
			block = trim_quote(block, &i);
			//printf("block D_QUOTE = %s\n", block);
			//Expand nos dollars dans notre block
			block = expand_dollar(env, block);
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
	return (expanded);

}

t_token	*expand_all(char **env, t_token *all)
{
	t_token	*tmp;

	tmp = all;
	while (tmp)
	{
		tmp->content = expand_node(env, tmp->content);
		if (!tmp->content)
			return (NULL);
		tmp = tmp->next;
	}
	return (all);
}

/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_token		*temp;
	t_token		*expanded;
	t_command	*cmd_all;
	(void)cmd_all;

	temp = lexer(ft_strdup("echo  $\"$USER\"$"));
	printf("LEXER :\n");

	expanded = expand_all(envp, temp);
	print_token(&expanded);
	cmd_all = token_to_cmd(expanded);
	//printf("EXPAND :\n");
	//print_cmd(&cmd_all);
	//print_cmd(&cmd_all);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	return (0);
} */

/* int main(int argc, char **argv, char **envp)
{
	char	**env;
	(void)argc;
	(void)argv;
	//t_token *temp;
	//t_token	*expanded;
	char	*ret_trim;

	char	*arg;
	env = NULL;
	arg = ft_strdup("\"$USER   \'$USER\' \' \' \"\'$USER\'");
	env = ft_create_env(envp);
	ret_trim = expand_node(env, arg);
	printf("ret_trim = |%s|\n", ret_trim);
	ft_free_tab_2d(env);
} */