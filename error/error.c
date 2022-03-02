# include "../includes/function.h"

void	ft_print_error(int minishell, char *cmd_name, char *error, char *token)
{
	if (minishell == 1)
		ft_putstr_fd(BRED"minishell: ", STDERR_FILENO);
	if (cmd_name != NULL)
	{
		ft_putstr_fd(BRED"", STDERR_FILENO);
		ft_putstr_fd(cmd_name, STDERR_FILENO);
	}
	if (token == NULL)
		ft_putstr_fd(error, STDERR_FILENO);
	else
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putstr_fd("\n" CRESET, STDERR_FILENO);
}