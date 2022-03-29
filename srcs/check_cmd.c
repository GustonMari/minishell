/* #include "../includes/function.h" */

/* */

/* int	is_valid_cmd(char **env, char **full_cmd)
{
	char	*new_cmd;
	char	*path;
	char	*tmp;

	tmp = find_val_in_tab(env, "PATH");
	if (!tmp)
		return (-1);
	new_cmd = ft_strjoin("/", full_cmd[0]);
	if (!new_cmd)
		return (-1);
	path = find_path_cmd(new_cmd, tmp);
	if (!path)
		return (-1);
	free(path);
	return (0);
} */

/* Permet de checker si toutes les commandes existent dans t_command,
si une commande n'existe pas on affiche un message d'erreur avec le nom de la cmd qui n'existe pas
Attention, il faut quand meme continuer a executer les autres commandes dans les autres pipes
*/

/* int	check_t_cmd(char **env, t_command *all)
{
	t_command *tmp;

	tmp = all;
	while (tmp)
	{
		if (is_valid_cmd(env, tmp->cmd_to_exec) == -1)
		{
			ft_putstr_fd(BRED tmp->cmd_to_exec[0] CRESET, 2);
			perror(BRED ": command not found" CRESET);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
} */