
#include "../includes/function.h"

/* 			tmp = ft_strtrim(strs[i], " \t\n\v\f\r");
			free(strs[i]);
			strs[i] = tmp; */

/* char	**trim_space_one(char **strs)
{
	int	i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (strs[i])
	{
		if (strs[i][0] != QUOTE && strs[i][0] != D_QUOTE)
		{
			tmp = ft_strtrim_space;
		}
		i++;
	}
	return (strs);
} */

char	**trim_quote(char **strs)
{
	int	i;
	char *tmp;

	tmp = NULL;
	i = 0;
	while (strs[i])
	{
		if (strs[i][0] == QUOTE)
		{
			tmp = ft_strtrim(strs[i], "\'");
			free(strs[i]);
			strs[i] = tmp;
		}
		else if (strs[i][0] == D_QUOTE)
		{
			tmp = ft_strtrim(strs[i], "\"");
			free(strs[i]);
			strs[i] = tmp;
		}
		i++;
	}
	return (strs);
}

/* int	main()
{
	char	*str = " \"salut   \"         ok LOL\'pain\'";
	char	**strs;
	//char 	**ret;

	strs = ft_split_special(str);


	//ret = trim_quote(strs);
	//print_tab_2d(strs);
	//ft_free_tab_2d(strs);
	print_tab_2d(strs);
	ft_free_tab_2d(strs);
	return (0);
} */

