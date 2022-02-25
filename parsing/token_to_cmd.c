#include "../includes/function.h"

/*Trouve la taille du tableau a deux dimmensions qui va etre cree pour une commande*/

int cmd_len(t_token *tokens)
{
    int count;

    count = 0;
    while (tokens && !is_operator(tokens->content))
    {
        tokens = tokens->next;
        count++;
    }
	return (count);
}

/* Cree un tab a deux dimmensions avec un NULL a la fin pour une commande et ses arguments*/

char	**token_to_tab(t_token *tokens)
{
    char	**strs;
	int		i;

	i = 0;
	strs = ft_calloc(sizeof(char *), (cmd_len(tokens) + 1));
	if (!strs)
		return (NULL);
	while (tokens && !is_operator(tokens->content))
    {
		strs[i] = ft_strdup(tokens->content);
		if (!strs[i])
			return (ft_free_tab_2d(strs));
		tokens = tokens->next;
		i++;
    }
	strs[i] = NULL;
	return (strs);
}

/* Cree un tab a deux dimmensions avec un NULL a la fin pour un operateur*/

char	**token_op_to_tab(t_token *tokens)
{
    char	**strs;

	strs = ft_calloc(sizeof(char *), (2));
	if (!strs)
		return (NULL);
	strs[0] = ft_strdup(tokens->content);
	if (!strs[0])
		return (ft_free_tab_2d(strs));
	strs[1] = NULL;
	return (strs);
}

/*Cree un Node de cmd, assigne le type et fait pointer vers son tab a deux dimmensions*/

t_command	*create_new_cmd_node(char **strs, t_token *all)
{
	t_command *new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_to_exec = strs;
	if (!new_cmd->cmd_to_exec)
		return (NULL);
	new_cmd->type = all->type;
	new_cmd->next = NULL;
	return (new_cmd);
}


void	ft_add_back_cmd(t_command **alst, t_command *new)
{
	t_command	*temp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

/* Transforme notre liste token en liste de cmd*/

t_command   *token_to_cmd(t_token *all)
{
    t_command   *cmd_all;
	t_token		*tmp_token;

	cmd_all = NULL;
	tmp_token = all;
    while (tmp_token)
    {	
		if (!is_operator(tmp_token->content))
			ft_add_back_cmd(&cmd_all, create_new_cmd_node(token_to_tab(tmp_token), tmp_token));
		while (tmp_token && !is_operator(tmp_token->content))
			tmp_token = tmp_token->next;
		if (tmp_token && is_operator(tmp_token->content))
			ft_add_back_cmd(&cmd_all, create_new_cmd_node(token_op_to_tab(tmp_token), tmp_token));
        if (tmp_token)
			tmp_token = tmp_token->next;
    }
    return (cmd_all);
}

int main(int argc, char **argv, char **envp)
{

	char	**env;
	(void)argc;
	(void)argv;
	t_token *temp;
	t_token	*expanded;
	t_command *cmd_all;
	(void)cmd_all;


	char	*arg;
	env = NULL;
	arg = ft_strdup(" \"ca\" |	<	><	> \r	sal	ut poe	ut");
	env = ft_create_env(envp);
	temp = lexer(arg);
	expanded = expand_all(env, temp);
	trim_all(&expanded);
	//print_token(&expanded);
	cmd_all = token_to_cmd(expanded);
	print_cmd(&cmd_all);
	ft_lstclear(&expanded, free);
	ft_cmd_clear(&cmd_all);
	ft_free_tab_2d(env);
}
