#include "../includes/function.h"

/*Permet de supprimer les fichiers temporaires .heredoc*/

int	delete_heredoc_file(t_command *all_cmd)
{
	t_command	*tmp;

	tmp = all_cmd;
	while(tmp)
	{
		if (tmp->to_del == 1)
		{
			if (unlink(tmp->cmd_to_exec[0]) < 0)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*Permet de savoir si le dernier element du tableau stop
possede des quotes ou non. Si il possede des quote on renvoie
0, et on expandra pas. Si il n'en possede pas on revoie 1 et 
on expandra*/

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
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*Permet de compter combien il y a de quote dans le tableau str*/

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
	return (count);
}

/*Cette fonction permet d'enlever les quote dans un tableau
normal*/

char	*trim_line_stop(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_calloc(sizeof(char), (ft_strlen(str) - count_quote(str) + 2));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i] != QUOTE && str[i] != D_QUOTE)
		{
			ret[j] = str[i];
			i++;
			j++;
		}
		else
			i++;
	}
	ret[j] = '\0';
	return (ret);
}

/*Permet d'enlever les quotes dans le tableau stop, qui regroupe les
limitor du heredoc, renvoie ce tableau Stop*/

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
		ret[i] = trim_line_stop(strs[i]);
		if (!ret)
			return (NULL);
		i++;
	}
	ft_free_tab_2d(strs);
	return (ret);
}

/* int	main(int ac, char **av, char **envp)
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
    char *line = ft_strdup("ls << ls << \"p\"o\"uet\" < lolwesh");
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
} */