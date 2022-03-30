
#include "../includes/function.h"

long long	ft_atolll(char *str)
{
	unsigned long long atoll;
	int						neg;

	neg = 1;
	atoll = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str)
	{
		atoll = atoll * 10 + *str - 48;
		str++;
	}
	return ((long long)atoll * neg);
}