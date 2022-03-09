/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:29:31 by gmary             #+#    #+#             */
/*   Updated: 2022/03/08 17:22:04 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "struct.h"
# include "colors.h"
# include "get_next_line.h"
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
# define QUOTE '\''
# define D_QUOTE '\"'

# define FT_CD 1
# define FT_PWD 2
# define FT_ENV 3
# define FT_UNSET 4
# define FT_EXPORT 5
# define FT_ECHO 6
/*
--------------- LIST UTILS ----------------
*/

t_token	*ft_lstnew(char *content, t_tokentype type);
void	ft_lstadd_back(t_token **alst, t_token *new);
void    print_token(t_token **begin_list);
void    print_cmd(t_command **begin_list);

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
//char	**ft_export(char **env, char *str);
int		ft_count_line(char **tab);
int		ft_is_space(char c);

/*
--------------- UTILS 3 ----------------
*/

char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strjoin_free(char *s1, char *s2, int del);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
void	print_tab_2d(char **strs);

/*
--------------- UTILS 4 ----------------
*/

char	*ft_strtrim(char *s1, char *set);
void	print_tab_2d(char **strs);
int	    ft_isalnum(int c);


/*
--------------- ft_cd.c ----------------
*/

int	ft_cd(char **full_cmd, char **env);
int		ft_home(char **env);

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
char	*find_name_val(char *str);
char	*find_val_in_line(char *str);
char	**manage_export(char **env, char **full_cmd);
int		ft_print_export_no_arg(char **env);
int     ft_check_export(char *str);
char	**bubble_sort_tab_2d(char **tab);
char	*find_name_val(char *str);
char	*find_val_in_line(char *str);
/*
------------------ CLEAR ----------------
*/

char	**ft_free_tab_2d(char **tab);
void	ft_lstclear(t_token **lst, void (*del)(void *));
void	ft_cmd_clear(t_command **lst);

/*
------------------ UNSET ----------------
*/

int	is_var_in_line(char *str, char *to_del, size_t n);
char	**ft_unset(char **env, char **full_cmd);


/*
------------------ PWD ----------------
*/

int	ft_pwd(void);
char	*ft_pwd_return(void);

/*
------------------ REDIRECTION ----------------
*/

int		redirection_to_file(char *file_name, char *str);
int		manage_chv_l(t_command *all_cmd, int *in);
int		manage_chv_r(t_command *all_cmd, int *out);
int		redirection(t_command *all_cmd, int *in, int *out);
int		is_redirection_type(t_command *op);
int	    count_cmd_between_pipe(t_command *all_cmd);
int     count_redir(t_command *all_cmd);

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

t_token	*lexer(char *arg);

/*
------------------QUOTE ----------------
*/

int check_quote(char *arg);
int	find_next_quote(char *str);

/*
------------------EXEC ----------------
*/

char	*find_path_cmd(char *cmd, char *tmp);
int	ft_exec(char **env, char **full_cmd);
int	ft_exec_cmd(char **env, char **full_cmd);
char	**ft_dispatch(t_command *all, char **env);

/*
------------------EXECUTE 1 ----------------
*/

char	**execute_one_cmd(char **env, t_command *all);
/*
------------------CHECK ----------------
*/
int	is_operator(char *operator);
int	is_built_cmd(char **env, char *cmd);
int	is_cmd(char **env, char *cmd);
int	is_builtin(char *builtin);
int	check_cmd_list(t_command *all);
int	is_operator_type(t_command *op);

/*
------------------CHECK CMD----------------
*/

int	check_t_cmd(char **env, t_command *all);

/*
------------------ $$ DOLLARZ $$ ----------------
*/

char	*expand_dollar(char **env, char *str);

/*
------------------ EXPAND ----------------
*/

t_token	*expand_all(char **env, t_token *all);

/*
------------------ PARSING ----------------
*/

//NEW TRIM QUOTE
char	*trim_quote(char *str, int *i);
char	*expand_single_dollar(char **env, char *str);

//char	*trim_quote(char *str);
char	**ft_split_special(char *str);
char	*ft_strtrim_space(char *s1, char *set);
t_token	*trim_all(t_token **all);
t_command	*token_to_cmd(t_token *all);
int	cmd_len(t_token *tokens);
char	**token_to_tab(t_token *tokens);
char	**token_op_to_tab(t_token *tokens);
t_command	*create_new_cmd_node(char **strs, t_token *all);
void	ft_add_back_cmd(t_command **alst, t_command *new);


/* 
------------------ CALLOC ----------------
*/

void	*ft_calloc(size_t nmemb, size_t size);


/* 
------------------ TOKEN_TO_CMD ----------------
*/

t_command   *token_to_cmd(t_token *all);

/* 
------------------ MANAGER ----------------
*/

char	**manage_line(char **env, char *line);

/* 
------------------ PIPE ------------------
*/

//int execute_pipe(t_command *all_cmd, char **env, int nb_cmd);
int		execute_pipe(t_command *all_cmd, char **env, int nb_cmd, int in);
int		count_cmd_list(t_command *all_cmd);
int		count_all_between_pipe(t_command **all_cmd);

/* 
------------------ ERROR ------------------
*/

void	ft_print_error(int minishell, char *cmd_name, char *error, char *token);
void	cd_error(char *cmd, int to_many_arg);

/* 
------------------ ECHO ------------------
*/

void ft_echo(char **full_cmd);

/* 
------------------ WAIT ------------------
*/

int	wait_pipe(int nb_cmd);

/* 
------------------ GNL ------------------
*/
char	*get_next_line(int fd);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

#endif
