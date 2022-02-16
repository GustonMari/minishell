
#include "function.h"

char	*ft_pwd_return(void)
{
	char	*buff;
	char	*ret;

	buff = NULL;
	ret = getcwd(buff, BUFFER_SIZE);
	if (ret == NULL)
	{
		if (errno == ERANGE)
			ft_putstr_fd("ERANGE ERROR\n", 2);
		return(NULL);
	}
	free(buff);
	return (ret);
}

int	ft_pwd(void)
{
	char	*buff;
	char	*ret;

	buff = NULL;
	ret = getcwd(buff, BUFFER_SIZE);
	if (ret == NULL)
	{
		if (errno == ERANGE)
			ft_putstr_fd("ERANGE ERROR\n", 2);
		return(-1);
	}
	else
	{
		ft_putstr_fd(ret, 1);
		ft_putchar_fd('\n', 1);
	}
		
	free(buff);
	free(ret);
	return (0);
}
