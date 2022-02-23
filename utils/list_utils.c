#include "../includes/function.h"

void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token	*temp;

	if (!*alst)
	{
		*alst = new;
		/* printf("new %s \n", new->content); */
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_token	*ft_lstnew(char *content, t_tokentype param)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	//new->content = malloc(sizeof(char) * (ft_strlen(content) + 1));
	new->content = content;

	if (!new->content)
		return (NULL);
	new->content = content;
	new->type = param;
	new->next = NULL;
	return (new);
}

void    print_token(t_token **begin_list)
{
    t_token *current;

    current = *begin_list;
    while(current)
    {
		printf("%s\n", current->content);
		/* ft_putstr_fd(current->content, 1); */
		/* printf("\ntype = %d\n", (int)current->type); */
        /* ft_putchar_fd('\n', 1); */
        current = current->next;
    }
    //printf("NULL\n");
}