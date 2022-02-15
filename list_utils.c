#include "function.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

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



t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof(char) * ft_strlen(content) + 1);
	if (!new->content)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void    print_list(t_list **begin_list)
{
    t_list *current;

    current = *begin_list;
    while(current)
    {
		ft_putstr_fd(current->content, 1);
        ft_putchar_fd('\n', 1);
        current = current->next;
    }
    //printf("NULL\n");
}