
#include "../includes/function.h"

int	ft_free_tab_2d(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
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
			current = current ->next;
			(*del)(previous ->content);
			free(previous);
		}
		*lst = NULL;
	}
}