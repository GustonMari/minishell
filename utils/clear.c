#include "../includes/function.h"

char	**ft_free_tab_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		//if (tab[i])
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*previous;
	t_token	*current;

	if (lst && *lst && del)
	{
		current = *lst;
		while (current)
		{
			previous = current;
			current = current->next;
			(*del)(previous->content);
			free(previous);
		}
		*lst = NULL;
	}
}

void	ft_cmd_clear(t_command **lst)
{
	t_command	*previous;
	t_command	*current;

	if (lst && *lst)
	{
		current = *lst;
		while (current)
		{
			previous = current;
			current = current->next;
			ft_free_tab_2d(previous->cmd_to_exec);
			free(previous);
		}
		*lst = NULL;
	}
}
