/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:29:31 by gmary             #+#    #+#             */
/*   Updated: 2022/02/15 13:31:30 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "struct.h"
# include "colors.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <termios.h>
# define BUFFER_SIZE 200


/*
--------------- LIST UTILS ----------------
*/

t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void    print_list(t_list **begin_list);

/*
--------------- UTILS ----------------
*/

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

char	*ft_strdup(const char *src);



/*
--------------- ft_cd.c ----------------
*/

int		ft_cd(char *str);
int		ft_home(void);

/*
------------------ ENV ----------------
*/
/* t_list	**ft_create_env(char **envp);
int	ft_print_env(t_list **env); */
char	**ft_create_env(char **envp);
int		ft_print_env(char **env);


#endif
