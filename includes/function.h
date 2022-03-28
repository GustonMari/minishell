/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:29:31 by gmary             #+#    #+#             */
/*   Updated: 2022/03/28 17:54:54 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "struct.h"
# include "colors.h"
# include "define.h"

/*
--------------- LIST UTILS ----------------
*/

t_token	*ft_lstnew(char *content, t_tokentype type);
void	ft_lstadd_back(t_token **alst, t_token *new);
void	print_token(t_token **begin_list);
void	print_cmd(t_command **begin_list);
int		ft_lstsize(t_token *lst);


/*
--------------- UTILS ----------------
*/

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	**shell_lvl(char **env);
int		ft_find_d_chv_l_str(char *str, char *c, int size);


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
int		ft_isalnum(int c);




/*
--------------- ft_cd.c ----------------
*/

int		ft_cd(char **full_cmd, char **env);
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
int		ft_check_export(char *str);
char	**bubble_sort_tab_2d(char **tab);
char	*find_name_val(char *str);
char	*find_val_in_line(char *str);
int		is_var_in_line_export(char *str, char *var, size_t n);
int		is_var_in_env_export(char **env, char *var, size_t n);
int		ft_change_env_val_export(char **env, char *var, char *new_val);
int		is_var_in_env_export_2(char **env, char *var, size_t n);

/*
------------------ CLEAR ----------------
*/

char	**ft_free_tab_2d(char **tab);
void	ft_lstclear(t_token **lst, void (*del)(void *));
void	ft_cmd_clear(t_command **lst);

/*
------------------ UNSET ----------------
*/

int		is_var_in_line(char *str, char *to_del, size_t n);
char	**ft_unset(char **env, char **full_cmd);
int		is_var_in_line_unset(char *str, char *to_del, size_t n);


/*
------------------ PWD ----------------
*/

int		ft_pwd(void);
char	*ft_pwd_return(void);

/*
------------------ REDIRECTION ----------------
*/

int		redirection_to_file(char *file_name, char *str);
int		manage_chv_l(t_command *all_cmd, char **env);
int		manage_chv_r(t_command **all_cmd);
int		redirection(t_command *all_cmd, int *in, int *out, char **env);
int		is_redirection_type(t_command *op);
int		count_cmd_between_pipe(t_command *all_cmd);
int		count_redir(t_command *all_cmd);
int		redirection_manager(t_command **all_cmd, char **env);
int		redirection_clean(t_command *all_cmd);

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
int		count_word_btw_two_op(t_token *all);
void	mv_word_left(t_token *all);
void	mv_chv_l(t_token *all);
int		count_word_btw_two_op(t_token *all);
void	remix_manager(t_token **all);
int		token_is_redir(t_token *tmp_token);


/*
------------------QUOTE ----------------
*/

int		check_quote(char *arg);
int		find_next_quote(char *str);

/*
------------------EXEC ----------------
*/

char	*find_path_cmd(char *cmd_to_join, char *tmp);
char	*chose_ath_cmd(char *cmd, char *tmp);
int		ft_exec(char **env, t_command *all_cmd, t_to_clean *clean, int out);
int		ft_exec_cmd(char **env, t_to_clean *clean, t_command *all, int out);
char	**ft_dispatch(t_command *all, t_to_clean *clean, char **env);

/*
------------------EXECUTE 1 ----------------
*/

char	**execute_one_cmd(char **env, t_to_clean *clean, t_command *all);
/*
------------------CHECK ----------------
*/
int		is_operator(char *operator);
int		is_built_cmd(char **env, char *cmd);
int		is_cmd(char **env, char *cmd);
int		is_builtin(char *builtin);
int		check_cmd_list(t_token *all);
int		is_operator_type(t_command *op);

/*
------------------CHECK CMD----------------
*/

int		check_t_cmd(char **env, t_command *all);

/*
------------------ $$ DOLLARZ $$ ----------------
*/

char	*expand_dollar(char **env, char *str);
char	*replace_dollar_3(char *str, char *new_var, char *ret);
char	*replace_interrogation(char *str, int pos);
char	*replace_dollar_2(char *str, char *new_var, char *ret, int pos);


/*
------------------ EXPAND ----------------
*/

t_token	*expand_all(char **env, t_token *all);
char	*cpy_block(char	*str, int size);
char	*expand_node_single(char **env, char *str);
int		find_next_block(char *str);

/*
------------------ PARSING ----------------
*/

//NEW TRIM QUOTE
char		*trim_quote(char *str, int *i);
char		*expand_single_dollar(char **env, char *str);

//char		*trim_quote(char *str);
char		**ft_split_special(char *str);
char		*ft_strtrim_space(char *s1, char *set);
t_token		*trim_all(t_token **all);
t_command	*token_to_cmd(t_token *all);
int			cmd_len(t_token *tokens);
char		**token_to_tab(t_token *tokens);
char		**token_op_to_tab(t_token *tokens);
t_command	*create_new_cmd_node(char **strs, t_token *all);
void		ft_add_back_cmd(t_command **alst, t_command *new);
int			token_is_operator(t_token *tmp_token);



/* 
------------------ CALLOC ----------------
*/

void		*ft_calloc(size_t nmemb, size_t size);


/* 
------------------ TOKEN_TO_CMD ----------------
*/

t_command	*token_to_cmd(t_token *all);

/* 
------------------ MANAGER ----------------
*/

char		**manage_line(char **env, char *line);

/* 
------------------ PIPE ------------------
*/

//int execute_pipe(t_command *all_cmd, char **env, int nb_cmd);
int 		execute_pipe(t_command *all_cmd, t_to_clean *clean, char **env, int in);
int			count_cmd_list(t_command *all_cmd);
int			count_all_between_pipe(t_command **all_cmd);

/* 
------------------ ERROR ------------------
*/

void		ft_print_error(int minishell, char *cmd_name, char *error, char *token);
void		cd_error(char *cmd, int to_many_arg);
int			redirection_error(char *file_name);
int			print_cmd_error(char *str);


/* 
------------------ ECHO ------------------
*/

void		ft_echo(char **full_cmd);

/* 
------------------ WAIT ------------------
*/

int			wait_pipe(void);
void		exit_pipe_process(int sig);

/* 
------------------ HEREDOC ------------------
*/

int			priorities_D_CHV_L(t_command *all_cmd);
int			launch_heredoc(t_command **all_cmd, char **env, char *name, t_to_clean *clean);
int			manage_heredoc(t_command **all_cmd, char **env, t_to_clean *clean);
int			delete_heredoc_file(t_command *all_cmd);
int			count_nb_D_CHV_L_between_pipe(t_command *all_cmd);
int			create_heredoc_file(char *name);
int			start_heredoc_one(char **stop, int begin);
int			start_heredoc_more(char **stop, int i);
void		exit_heredoc(int sig);
int			signal_heredoc(void);
char		**create_tab_stop(t_command *all_cmd);
char		**trim_quote_stop(char **strs);
int			is_expand_heredoc(char **stop);


/* 
------------------ ITOA ------------------
*/
char		*ft_itoa(int n);
int			ft_lennum(int n);

/* 
------------------ IS_DIGIT ------------------
*/
int			is_str_digit(char *str);

/* 
------------------ EXIT_ERROR ------------------
*/
void		exit_error(char *filename);

/* 
------------------ ATOI ------------------
*/

int			ft_atoi(const char *str);

/* 
------------------ EXIT ------------------
*/

void		ft_exit(t_command *all, t_to_clean *clean);
void		ft_clean_exit(t_to_clean *clean);

/* 
------------------ SIGNAL ------------------
*/

void	signal_in_cmd(void);
void	signal_manager2(void);
void	signal_cmd(int sig);





int	prio_exit(t_command *all);

#endif
