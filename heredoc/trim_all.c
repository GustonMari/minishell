#include "../includes/function.h"

int	is_expand_heredoc(char **stop)
{
	int	last;
	int	i;

	i = 0;
	last = ft_count_line(stop) - 1;
	while (stop[last][i])
	{
		if (stop[last][i] == QUOTE
			|| stop[last][i] == D_QUOTE)
			return (0);
		i++;
	}
	return (1);
}

int	count_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE)
			count++;
		i++;
	}
	return (i);
}

char	*trim_line_stop(char *str, char *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ret[j] && str[i] && str[i] != QUOTE && str[i] != D_QUOTE)
		{
			ret[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	ret[j] = 0;
	return (ret);
}

char	**trim_quote_stop(char **strs)
{
	char	**ret;
	int		i;
	(void)i;

	i = 0;
	ret = NULL;
	ret = ft_calloc(sizeof(char *), (ft_count_line(strs) + 1));
	if (!ret)
		return (NULL);
	while (strs[i])
	{
		ret[i] = ft_calloc(sizeof(char), (ft_strlen(strs[i]) - count_quote(strs[i]) + 1));
		if (!ret[i])
			return (NULL);
		trim_line_stop(strs[i], ret[i]);
		if (!ret)
			return (NULL);
		i++;
	}
	ft_free_tab_2d(strs);
    return (ret);
}

int	main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_token *temp = NULL;
	t_token	*expanded = NULL;
	t_command *cmd_all = NULL;
	cmd_all = NULL;
    char **env = NULL;
	char **stop;
	
	stop = NULL;
	env = ft_create_env(envp);
    char *line = ft_strdup("ls << ls << po\"uet\" < lolwesh");
	temp = lexer(line);
	expanded = expand_all(env, temp);
	cmd_all = token_to_cmd(expanded);
	stop = create_tab_stop(cmd_all);
	stop = trim_quote_stop(stop);
	print_tab_2d(stop);
	//printf("result = %d\n", is_expand_heredoc(stop));
	//printf("Prio = %d\n", priorities_D_CHV_L(cmd_all));
    //ft_dispatch(cmd_all, env);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	ft_free_tab_2d(env);
	ft_free_tab_2d(stop);
    return (0);
}