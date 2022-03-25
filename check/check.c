/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:06:41 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/23 10:06:45 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/* Renvoie un nb positif si c'est un builtin, renvoie le num correspondant
au builtin*/

int	is_builtin(char *builtin)
{
	if (!ft_strcmp("cd", builtin))
		return (FT_CD);
	if (!ft_strcmp("pwd", builtin))
		return (FT_PWD);
	if (!ft_strcmp("env", builtin))
		return (FT_ENV);
	if (!ft_strcmp("unset", builtin))
		return (FT_UNSET);
	if (!ft_strcmp("export", builtin))
		return (FT_EXPORT);
	if (!ft_strcmp("echo", builtin))
		return (FT_ECHO);
	return (0);
}

/*Renvoie 0 c'est cmd est une commande */

int	is_cmd(char **env, char *cmd)
{
	char	*path;
	char	*tmp;

	tmp = find_val_in_tab(env, "PATH");
	if (!tmp)
		return (-1);
	path = chose_ath_cmd(cmd, tmp);
	if (!path)
	{
		free(path);
		ft_putstr_fd(BRED"minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n"CRESET, 2);
		g_status = 127;
		return (1);
	}
	free(path);
	return (0);
}

/*Renvoie 0 si cmd est une commande ou un builtin*/

int	is_built_cmd(char **env, char *cmd)
{
	if (!is_builtin(cmd) || is_cmd(env, cmd))
		return (1);
	return (0);
}

/* int	is_operator(char *operator)
{
	if (!ft_strcmp(">>", operator))
		return (D_CHV_R);
	if (!ft_strcmp("<<", operator))
		return (D_CHV_L);
	if (!ft_strcmp("|", operator))
		return (PIPE);
	if (!ft_strcmp(">", operator))
		return (CHV_R);
	if (!ft_strcmp("<", operator))
		return (CHV_L);

	return (0);
} */

//Save, working, probleme avec op <> |< ....

int	is_operator(char *operator)
{
	if (!ft_strncmp(">>", operator, 2))
		return (D_CHV_R);
	if (!ft_strncmp("<<", operator, 2))
		return (D_CHV_L);
	if (!ft_strncmp("|", operator, 1))
		return (PIPE);
	if (!ft_strncmp(">", operator, 1))
		return (CHV_R);
	if (!ft_strncmp("<", operator, 1))
		return (CHV_L);
	return (0);
}

/* int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char **env;

	env = ft_create_env(envp);
	printf("ret is_cmd = %d\n", is_cmd(env, "echo"));
	printf("ret builtin = %d\nret = is_built_cmd = %d", is_builtin("cd"), is_built_cmd(env, "ls"));
	ft_free_tab_2d(env);
	//ft_putstr_fd(BRED"salut ca va"CRESET, 1);
	return (0);
} */