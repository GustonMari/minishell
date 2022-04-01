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
	{
		free(str);
		return (NULL);
	}
	while (str[i])
	{
		if (i == pos_a && str[i])
			i++;
		if (i == pos_b && str[i])
		{
			i++;
			j++;
			break ;
		}
		ret[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	ret[j] = '\0';
	//WARNING
	free(str);
	return (ret);
}

char	*trim_quote(char *str, int *i, t_to_clean *clean)
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
			return (ft_clean_error_malloc(clean));
		
		*i += (j);
	}
	return (str);
}


char	*cpy_block_special(char	*str, int size, t_to_clean *clean)
{
	char	*block;

	block = malloc(sizeof(char) * ((size) + 1));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	block = ft_strncpy(block, str, ((unsigned int)size));
	return (block);
}

/*
		permet de copier une block, par exemple un block entre "" ou ''
*/

char	*cpy_block(char	*str, int size, t_to_clean *clean)
{
	char	*block;

	block = malloc(sizeof(char) * (size + 2));
	if (!block)
		return (ft_clean_error_malloc(clean));
	block = ft_strncpy(block, str, (unsigned int)size);
	return (block);
}

/*Trouve le prochain block qui commence par un $ ou Quote ou DQuote ou se termine par '\0'
et renvoie sa position*/

int	find_next_block(char *str)
{
	int	i;

	i = 0;
	if (str[0] && str[0] == '$')
		i++;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE || str[i] == '$' || str[i] == BACK_SLASH)
			return (i);
		i++;
	}
	return (i);
}


int	nb_back_slash(char *str)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
			nb ++;
		i++;
	}
	return (nb);
}

int	nb_dollar(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nb++;
		i++;
	}
	return (nb);
}

char	*add_echapment(char *str, t_to_clean *clean)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + nb_dollar(str) + 1));
	if (!new)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	while (str[i])
	{
		if (str[i] == '$')
		{
			new[j] = BACK_SLASH;
			j++;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

/*Supprime tous les backslash devant un dollar dans la string*/

char	*del_back_slash(char *str, t_to_clean *clean)
{
	int		i;
	int		j;
	int		nb;
	char	*block;

	i = 0;
	j = 0;
	nb = 0;
	nb = nb_back_slash(str);
	block = malloc(sizeof(char) * (ft_strlen(str) + 1 - nb));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
		
	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
			i++;
		block[j] = str[i];
		i++;
		j++;
	}
	block[j] = '\0';
	free(str);
	return (block);
}

/*Expand un maillon */

char	*expand_node(char **env, char *str, t_to_clean *clean)
{
	int		i;
	char	*block;
	char	*expanded;
	(void)env;

	block = NULL;
	expanded = ft_strdup("");
	if (!expanded)
		return (ft_clean_error_malloc(clean));
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			block = trim_quote(block, &i, clean);
			block = add_echapment(block, clean);
		}
		else if (str[i] == D_QUOTE)
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			block = trim_quote(block, &i, clean);
			block = expand_dollar(env, block, clean);
		}
		else if (str[i] == '$')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]), clean);
			if (str[i + 1] != '\0')
				block = expand_single_dollar(env, block, clean);
			block = del_back_slash(block, clean);
			i += find_next_quote(&str[i]);
		}
		else if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			i++;
			block = cpy_block_special(&str[i], find_next_block(&str[i]), clean);
			i += find_next_block(&str[i]);
		}
		else
		{
			block = cpy_block(&str[i], find_next_block(&str[i]), clean);
			i += find_next_block(&str[i]);
		}
		expanded = ft_strjoin_free(expanded, block, 1);
		if (!expanded)
		{
			free(str);
			free(block);
			return (ft_clean_error_malloc(clean));
		}
		free(block);
	}
	free(str);
	return (expanded);

}

t_token	*expand_all(char **env, t_token *all, t_to_clean *clean)
{
	t_token	*tmp;
	int		expand;

	tmp = NULL;
	expand = 1;
	tmp = all;
	while (tmp)
	{
		if (expand)
		{
			tmp->content = expand_node(env, tmp->content, clean);
			if (!tmp->content)
				return (NULL);
		}
		expand = 1;
		if (tmp->type == D_CHV_L)
			expand = 0;
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