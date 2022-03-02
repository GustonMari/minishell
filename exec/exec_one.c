# include "../includes/function.h"

char	**execute_one_cmd(char **env, t_command *all)
{
	int	builtin;

	builtin = is_builtin(all->cmd_to_exec[0]);
	if (builtin == FT_CD)
		ft_cd(all->cmd_to_exec, env);
	if (builtin == FT_UNSET)
	{
		env = ft_unset(env, all->cmd_to_exec);
		if (!env)
			return (NULL); 
	}
	if (builtin == FT_EXPORT)
		env = ft_export(env, all->cmd_to_exec[1]);
	if (builtin == FT_PWD)
		ft_pwd();
	if (builtin == FT_ENV)
		ft_print_env(env);
	return (env);
	//return (0);
}