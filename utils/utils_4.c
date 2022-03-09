#include "../includes/function.h"

void	print_tab_2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

int	ft_isalnum(int c)
{
	if ((c < 48) || (c > 57 && c < 65) || ((c > 90) && (c < 97)) || (c > 122))
		return (0);
	else
		return (1);
}
