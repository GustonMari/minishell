#include "../includes/function.h"

void	print_tab_2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{

		fprintf(stderr,"%s\n", strs[i]);
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

int	ft_lstsize_cmd(t_command *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_lstsize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*Enleve le premier char c de str et retourne le nouveau str
sans ce permier char*/

char	*remove_char(char *str, char c)
{
	char	*new_str;
	int		i;
	int		first;

	i = 0;
	first = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str)));
	if (!new_str)
		return (NULL);
	while(str[i])
	{
		if (str[i] == c && first == 0)
		{
			first = 1;
			i++;
		}
		if (str[i])
			i++;
	}
	return (new_str);
}

/*Enleve le premier char c de str et retourne le nouveau str
sans ce permier char mais que si on est pas tombe sur le carac no*/
char	*remove_char_if(char *str, char c, char no)
{
	char	*new_str;
	int		i;
	int		j;
	int		first;

	j = 0;
	i = 0;
	first = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str)));
	if (!new_str)
		return (NULL);
	while(str[i])
	{
		if (str[i] == no)
			first = 1;
		if (str[i] == c && first == 0)
		{
			first = 1;
			i++;
		}
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}