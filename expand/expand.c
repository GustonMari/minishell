
#include "../includes/function.h"

int	find_next_quote(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\"')
	{
		i++;
		while (str[i] != '\"')
			i++;
		i++;
	}
	else if (str[0] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
		i++;
	}
	else
	{
		while (str[i] != '\"' && str[i] != '\'')
			i++;
	}
	printf("findnext = %d\n", i);
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

char	*expand_manager(char **env, char *str)
{
	int	i;
	char	*block;
	char	*expanded;

	expanded = NULL;
	i = 0;
	while(str[i])
	{
		if (str[i] == '\"')
		{
			block = cpy_block(&str[i], find_next_quote(&str[i]));
			// leaks
			block = expand_dollar(env, block);
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
		expanded = ft_strjoin(expanded, block);
		i += find_next_quote(&str[i]);
	}
	return (expanded);
}



int main(int argc, char **argv, char **envp)
{
	/* char	**env; */
	(void)argc;
	(void)argv;
	(void)envp;
	char *str;

	str = NULL;
	str = ft_strdup("salut ca va x\"ca    va\"");
	/* env = NULL;
	env = ft_create_env(envp); */
	printf("%s\n", cpy_block(&str[13], find_next_quote(&str[13])));
	
}