/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:29:31 by gmary             #+#    #+#             */
/*   Updated: 2022/02/21 09:35:38 by ndormoy          ###   ########.fr       */
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
# include <fcntl.h>
# define BUFFER_SIZE 200

# define PIPE 1
# define CHV_R 2
# define CHV_L 3
# define D_CHV_R 4
# define D_CHV_L 5
# define WORD 6

/*
--------------- LIST UTILS ----------------
*/

t_token	*ft_lstnew(char *content, t_tokentype type);
void	ft_lstadd_back(t_token **alst, t_token *new);
void    print_token(t_token **begin_list);

/*
--------------- UTILS ----------------
*/

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

/*
--------------- UTILS 2 ----------------
*/

char	*ft_strdup(char *src);
char	**ft_strdup_2d(char **srcs);
char	**ft_export(char **env, char *str);
int		ft_count_line(char **tab);
char	*ft_strjoin(char *s1, char *s2);

/*
--------------- UTILS 3 ----------------
*/

int	ft_is_space(char c);

/*
--------------- ft_cd.c ----------------
*/

int	ft_cd(char *str, char **env);
int	ft_home(char **env);

/*
------------------ ENV ----------------
*/
/* t_token	**ft_create_env(char **envp);
int	ft_print_env(t_token **env); */
char	**ft_create_env(char **envp);
int		ft_print_env(char **env);

/*
------------------ EXPORT ----------------
*/

char	**ft_export(char **envp, char *str);

/*
------------------ CLEAR ----------------
*/

int		ft_free_tab_2d(char **tab);
void	ft_lstclear(t_token **lst, void (*del)(void *));

/*
------------------ UNSET ----------------
*/

int	is_var_in_line(char *str, char *to_del, size_t n);


/*
------------------ PWD ----------------
*/

int	ft_pwd(void);
char	*ft_pwd_return(void);

/*
------------------ REDIRECTION ----------------
*/

int	redirection_to_file(char *file_name, char *str);

/*
------------------ ENV_UTILS ----------------
*/
char	*ft_cpy_val_var_env(char *var, char *find);
char	*find_val_in_tab(char **tab, char *find);
char	*ft_rpl_val_var_env(char *var, char *new_val);
int		ft_change_env_val(char **env, char *var, char *new_val);
char	*ft_find_env_line(char **env, char *var);
int		is_var_in_line(char *str, char *to_del, size_t n);

char	**ft_split(char const *s, char c);

/*
------------------ LEXER ----------------
*/

int	    define_operator(char *operator);


#endif
