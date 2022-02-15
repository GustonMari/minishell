
#include "function.h"

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