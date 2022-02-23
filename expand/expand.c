
#include "../includes/function.h"

int	find_next_quote(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\"')
	{
		i++;
		while (str[i] != '\"' && str[i])
			i++;
		i++;
	}
	else if (str[0] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
		i++;
	}
	else
	{
		while (str[i] != '\"' && str[i] != '\'' && str[i])
			i++;
	}
	return (i);
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

/*
		
*/
/*Expand un maillon */

char	*expand_node(char **env, char *str)
{
	int		i;
	char	*block;
	char	*expanded;

	block = NULL;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	i = 0;
	while(str[i])
	{
		if (str[i] == '\"')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			if (!block)
				return (NULL);
			block = expand_dollar(env, block);
			if (!block)
				return (NULL);
		}
		else if (str[i] == '\'')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
		}
		else
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			// leaks
			block = expand_dollar(env, block);
		}
		//leaks
		expanded = ft_strjoin_free(expanded, block, 1);
		i += find_next_quote(&str[i]);
	}
	free(block);
	return (expanded);
}

t_token	*expand_all(char **env, t_token *all)
{
	t_token	*tmp;

	tmp = all;
	while (tmp)
	{
		tmp->content = expand_node(env, tmp->content);
		if(!tmp->content)
			return (NULL);
		tmp = tmp->next;
	}
	return (all);
}

/* int main(int argc, char **argv, char **envp)
{
	char	**env;
	(void)argc;
	(void)argv;
	t_token *temp;
	t_token	*expanded;

	char	*arg;
	env = NULL;
	arg = ft_strdup("salut ca va $USER ");
	env = ft_create_env(envp);
	temp = lexer(arg);
	print_token(&temp);
	printf("\n");
	expanded = expand_all(env, temp);
	print_token(&expanded);



	ft_free_tab_2d(env);

} */

int main(int argc, char **argv, char **envp)
{
	char	**env;
	(void)argc;
	(void)argv;
	//(void)envp; 
	char *str;
	char *ret;

	ret = NULL;
	str = NULL;
	str = ft_strdup("ca \'va\' toi\"$USER\" \"oui\'ii\"");
	env = NULL;
	env = ft_create_env(envp);
	ret = expand_node(env, str);
	printf("%s\n", ret);
	ft_free_tab_2d(env);
	free(str);
	free(ret);
}