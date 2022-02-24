#include "../includes/function.h"

int check_double_quote(char *arg, int *i)
{
    *i += 1;
    while (arg[*i])
    {
        if (arg[*i] == D_QUOTE)
            return (0);
        *i += 1;
    }
    return (1);
}

int check_simple_quote(char *arg, int *i)
{
    *i += 1;
    while (arg[*i])
    {
        if (arg[*i] == QUOTE)
            return (0);
        *i += 1;
    }
    return (1);
}

int check_quote(char *arg)
{
    int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == QUOTE)
		{
		    if(check_simple_quote(arg, &i))
		        return (1);
		}
		else if (arg[i] == D_QUOTE)
		{
		    if(check_double_quote(arg, &i))
		        return (1);
		}
		i++;
	}
	return (0);
}

/* Permet de trouver la position de la prochaine quote en fonction de la quote en str[0]*/

int	find_next_quote(char *str)
{
	int	i;

	i = 0;
	if (str[0] == D_QUOTE)
	{
		i++;
		while (str[i] != D_QUOTE && str[i])
			i++;
		i++;
	}
	else if (str[0] == QUOTE)
	{
		i++;
		while (str[i] != QUOTE && str[i])
			i++;
		i++;
	}
	else
	{
		while (str[i] != D_QUOTE && str[i] != QUOTE && str[i])
			i++;
	}
	return (i);
}

/* int main()
{
    char *str = "     \'echo\" \'  \"lol  \' pouet\'         ";
    printf("result = %d\n", check_quote(str));
    return (0);
} */
