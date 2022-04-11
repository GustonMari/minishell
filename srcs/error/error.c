/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:09:42 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/11 11:51:31 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	exit_error(char *filename)
{
	ft_putstr_fd(BRED"minishell: exit: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": numeric argument required\n"CRESET, 2);
}

int	redirection_error(char *file_name)
{
	if (errno != 0)
	{
		ft_putstr_fd(BRED"minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n"CRESET, 2);
		free(file_name);
		g_status = errno;
	}
	return (1);
}

/* int	redirection_error(char *file_name)
{
	ft_putstr_fd(BRED"minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n"CRESET, 2);
	free(file_name);
	g_status = errno;
	return (1);
} */

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

void	cd_error(char *cmd, int to_many_arg)
{
	ft_putstr_fd(BRED"minishell: cd: ", STDERR_FILENO);
	if (to_many_arg == 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		ft_putstr_fd(""CRESET, STDERR_FILENO);
	}
	else
	{	
		ft_putstr_fd("too many arguments"CRESET, 2);
		ft_putstr_fd("\n", 2);
	}
}

int	print_cmd_error(char *str)
{
	ft_putstr_fd(BRED"minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n"CRESET, 2);
	g_status = 2;
	return (-1);
}
