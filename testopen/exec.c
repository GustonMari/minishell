/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:00:48 by gmary             #+#    #+#             */
/*   Updated: 2022/02/11 07:07:33 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "function.h"

int	main()
{
	char	*av[] = {NULL};
	char	*envp[] = {NULL};
	//execve("/mnt/nfs/homes/gmary/Documents/TAFF/minishell/./a.out", av, envp);
	execve("/Users/gustavemary/Documents/ProjetCode/VIM/CURSUS/r3/minishell/./a.out", av, envp);
	return (0);
}