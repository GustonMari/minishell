#include "../includes/function.h"

char	*del_quote(char *str, int pos_a, int pos_b)
{
	int	i;
	int	j;
	char *ret;

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
			i++;
		ret[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	ret[j] = '\0';
	free(str);
	return (ret);
}

char	*trim_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE)
		{
			j = find_next_quote(&str[i]);
			str = del_quote(str, i, (j + i - 1));
			if (!str)
				return (NULL);
			i += j;
		}
		if (str[i])
			i++;
	}
	return (str);
}

t_token	*trim_all(t_token **all)
{
	t_token	*tmp;

	tmp = *all;
	while (tmp)
	{
		tmp->content = trim_quote(tmp->content);
		if(!tmp->content)
			return (NULL);
		tmp = tmp->next;
	}
	return (*all);
}

int main(int argc, char **argv, char **envp)
{
	char	**env;
	(void)argc;
	(void)argv;
	t_token *temp;
	t_token	*expanded;

	char	*arg;
	env = NULL;
	arg = ft_strdup(" \"ca\" | \'va\' toi\"$USER\" > \"oui\'ii\"");
	env = ft_create_env(envp);
	temp = lexer(arg);
	print_token(&temp);
	printf("-------------------------\n");
	expanded = expand_all(env, temp);
	trim_all(&expanded);
	print_token(&expanded);
	ft_lstclear(&expanded, free);
	ft_free_tab_2d(env);
}

/* int	main()
{
	char	*str = NULL;
	char	*ret = NULL;
	str = ft_strdup("\" \' sa\"lut\"cava\"ou i  i\" sal\"");
	printf("str = %s\n", str);
	ret = trim_quote(str);
	printf("%s\n", ret);
	free(ret);
	return (0);
} */