/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:27:53 by gmary             #+#    #+#             */
/*   Updated: 2022/02/15 13:59:16 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

/* int main(void)
{
	char	*buff = NULL;
	char	*ret;
	
	if (chdir("/Users/gustavemary/Documents/ProjetCode/VIM/CURSUS/r3/minishell/testopen") == -1)
		printf("Error");
	ret = getcwd(buff, BUFFER_SIZE);
	//"/mnt/nfs/homes/gmary/Documents/TAFF/minishell";
	//if (getcwd(buff, BUFFER_SIZE) == NULL)
	if (ret == NULL)
	{
		if (errno == ERANGE)
			printf("ERANGE ERROR");
		exit(0);
	}
	else
		printf("getcwd %s\n", ret);
	
	printf("getenv %s\n", getenv("PWD"));
	//et = getcwd(buff, BUFFER_SIZE);
		//printf("%s\n", buff);
	free(buff);
	free(ret);
	return (0);
}
 */


int		ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}


char	**ft_create_env(char **envp)
{
	char	**env;
	int		line;
	int		i;

	i = 0;
	line = ft_count_line(envp);
	env = malloc(sizeof(char *) * line + 1);
	if (!env)
		return (NULL);
	while (i < line)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			//clear le tab..
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}



/* int	ft_print_env(t_list **env)
{
	print_list(env);
	return (0);
}

t_list	**ft_create_env(char **envp)
{
	int i = 0;
	t_list	**env = NULL;
	t_list	*temp = NULL;

	env = malloc(sizeof(t_list *));
	while (envp[i])
	{
		temp = ft_lstnew(envp[i]);
		// if !temp => ft_lst_clear()
		ft_lstadd_back(env, temp);
		i++;
	}

	return (env);
} */
