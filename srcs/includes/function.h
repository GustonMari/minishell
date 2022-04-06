/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:29:31 by gmary             #+#    #+#             */
/*   Updated: 2022/04/06 14:44:56 by gmary            ###   ########.fr       */
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

t_token		*ft_lstnew(char *content, t_tokentype param, t_to_clean *clean);
void		ft_lstadd_back(t_token **alst, t_token *new);
void		print_token(t_token **begin_list);
void		print_cmd(t_command **begin_list);
int			ft_lstsize(t_token *lst);

/*
--------------- UTILS ----------------
*/

int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
char		**shell_lvl(char **env);
int			ft_find_d_chv_l_str(char *str, char *c, int size);
long long	ft_atolll(char *str);

/*
--------------- UTILS 2 ----------------
*/

char		*ft_strdup(char *src);
char		**ft_strdup_2d(char **srcs);
int			ft_count_line(char **tab);
int			ft_is_space(char c);

/*
--------------- UTILS 3 ----------------
*/

char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		*ft_strjoin_free(char *s1, char *s2, int del);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char *s, int start, int len);
void		print_tab_2d(char **strs);

/*
--------------- UTILS 4 ----------------
*/

char		*ft_strtrim(char *s1, char *set);
void		print_tab_2d(char **strs);
int			ft_isalnum(int c);

/*
--------------- ft_cd.c ----------------
*/

int			ft_cd(char **full_cmd, char **env);
int			ft_home(char **env);

/*
------------------ ENV ----------------
*/

char		**ft_create_env(char **envp);
int			ft_print_env(char **env);

/*
------------------ EXPORT ----------------
*/

char		**ft_export(char **envp, char *str);
char		*find_name_val(char *str);
char		*find_val_in_line(char *str);
char		**manage_export(char **env, char **full_cmd);
int			ft_print_export_no_arg(char **env);
int			ft_check_export(char *str);
char		**bubble_sort_tab_2d(char **tab);
char		*find_name_val(char *str);
char		*find_val_in_line(char *str);
int			is_var_in_line_export(char *str, char *var, size_t n);
int			is_var_in_env_export(char **env, char *var, size_t n);
int			ft_change_env_val_export(char **env, char *var,
				char *new_val, char *str);
int			is_var_in_env_export_2(char **env, char *var, size_t n);
char		*remove_char_if(char *str, char c, char no, int first);
int			is_equal_in_line(char *str);
void		ft_export_no_arg(char **env);

/*
------------------ CLEAR ----------------
*/

//char		**ft_free_tab_2d(char **tab);
void		*ft_free_tab_2d(char **tab);
void		ft_lstclear(t_token **lst, void (*del)(void *));
void		ft_cmd_clear(t_command **lst);
t_command	*ft_cmdclear_between_pipe(t_command **lst);

/*
------------------ UNSET ----------------
*/

int			is_var_in_line(char *str, char *to_del, size_t n);
char		**ft_unset(char **env, char **full_cmd);
int			is_var_in_line_unset(char *str, char *to_del, size_t n);
int			check_already_exists(char **env, char *to_del, size_t n);

/*
------------------ PWD ----------------
*/

int			ft_pwd(void);
char		*ft_pwd_return(void);

/*
------------------ REDIRECTION ----------------
*/

int			redirection_to_file(char *file_name, char *str);
//int			manage_chv_l(t_command *all_cmd, char **env);
int			manage_chv_l(t_command *all_cmd);

int			manage_chv_r(t_command **all_cmd);
int			redirection(t_command *all_cmd, int *in, int *out, char **env);
int			is_redirection_type(t_command *op);
int			count_cmd_between_pipe(t_command *all_cmd);
int			count_redir(t_command *all_cmd);
//int			redirection_manager(t_command **all_cmd, char **env);
int			redirection_manager(t_command **all_cmd);
int			redirection_clean(t_command *all_cmd);

/*
------------------ ENV_UTILS ----------------
*/
char		*ft_cpy_val_var_env(char *var, char *find);
char		*find_val_in_tab(char **tab, char *find);
char		*ft_rpl_val_var_env(char *var, char *new_val);
int			ft_change_env_val(char **env, char *var, char *new_val);
char		*ft_find_env_line(char **env, char *var);
int			is_var_in_line(char *str, char *to_del, size_t n);
char		**ft_split(char const *s, char c);

/*
------------------ LEXER ----------------
*/

t_token		*lexer(t_to_clean *clean, char *arg);
int			count_word_btw_two_op(t_token *all);
void		mv_word_left(t_token *all);
void		mv_chv_l(t_token *all);
int			count_word_btw_two_op(t_token *all);
void		remix_manager(t_token **all);
int			token_is_redir(t_token *tmp_token);

/*
--------------REMIX 2-----------------
*/

void		remix_2(t_command **all_cmd);

/*
------------------QUOTE ----------------
*/

int			check_quote(char *arg);
int			find_next_quote(char *str);

/*
------------------EXEC ----------------
*/

char		*find_path_cmd(char *cmd_to_join, char *tmp);
char		*chose_ath_cmd(char *cmd, char *tmp);
int			ft_exec(char **env, t_command *all_cmd, t_to_clean *clean, int out);
int			ft_exec_cmd(char **env, t_to_clean *clean, t_command *all, int out);
char		**ft_dispatch(t_command *all, t_to_clean *clean, char **env);

/*
------------------EXECUTE 1 ----------------
*/

char		**execute_one_cmd(char **env, t_to_clean *clean, t_command *all);
/*
------------------CHECK ----------------
*/
int			is_operator(char *operator);
int			is_built_cmd(char **env, char *cmd);
int			is_cmd(char **env, char *cmd);
int			is_builtin(char *builtin);
int			check_cmd_list(t_token *all);
int			is_operator_type(t_command *op);

/*
------------------CHECK CMD----------------
*/

int			check_t_cmd(char **env, t_command *all);

/*
------------------ $$ DOLLARZ $$ ----------------
*/

char		*expand_dollar(char **env, char *str, t_to_clean *clean);
char		*replace_dollar_3(char *str, char *new_var, char *ret);
char		*replace_interrogation(char *str, int pos,
				t_to_clean *clean, char *var_name);
char		*replace_dollar_2(char *str, char *new_var, char *ret, int pos);
/*
------------------ EXPAND ----------------
*/

t_token		*expand_all(t_token *all, t_to_clean *clean);
char		*cpy_block(char	*str, int size, t_to_clean *clean);
char		*expand_node_single(t_to_clean *clean, char **env, char *str);
int			find_next_block(char *str);

/*
------------------ PARSING ----------------
*/

char		*trim_quote(char *str, int *i, t_to_clean *clean);
char		*expand_single_dollar(char **env, char *str, t_to_clean *clean);
char		**ft_split_special(char *str);
char		*ft_strtrim_space(char *s1, char *set);
t_token		*trim_all(t_token **all);
t_command	*token_to_cmd(t_token *all, t_to_clean *clean);
int			cmd_len(t_token *tokens);
char		**token_to_tab(t_token *tokens, t_to_clean *clean);
char		**token_op_to_tab(t_token *tokens, t_to_clean *clean);
t_command	*create_new_cmd_node(char **strs, t_token *all, t_to_clean *clean);
void		ft_add_back_cmd(t_command **alst, t_command *new);
int			token_is_operator(t_token *tmp_token);

/* 
------------------ CALLOC ----------------
*/

void		*ft_calloc(size_t nmemb, size_t size);

/* 
------------------ MANAGER ----------------
*/

char		**manage_line(char **env, char *line);

/* 
------------------ PIPE ------------------
*/

int			execute_pipe(t_command *all_cmd, t_to_clean *clean,
				char **env, int in);
int			count_cmd_list(t_command *all_cmd);
int			count_all_between_pipe(t_command **all_cmd);

/* 
------------------ ERROR ------------------
*/

void		ft_print_error(int minishell, char *cmd_name,
				char *error, char *token);
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

int			priorities_d_chv_l(t_command *all_cmd);
int			launch_heredoc(t_command **all_cmd, char *name,
				t_to_clean *clean);
int			manage_heredoc(t_command **all_cmd, t_to_clean *clean);

int			delete_heredoc_file(t_command *all_cmd);
int			count_nb_d_chv_l_between_pipe(t_command *all_cmd);
int			create_heredoc_file(char *name);
int			start_heredoc_one(char **stop, int begin);
int			start_heredoc_more(char **stop, int i);
void		exit_heredoc(int sig);
int			signal_heredoc(void);
char		**create_tab_stop(t_command *all_cmd);
char		**trim_quote_stop(char **strs);
int			is_expand_heredoc(char **stop);
void		manage_heredoc_signal(int sig);
void		fill_heredoc_file(char **stop, int is_expand,
				char *name, t_to_clean *clean);
int			replace_heredoc(t_command **all_cmd, char *name);
int			signal_launch_heredoc(void);
int			remix_size_three(t_token *lst);
t_to_clean	*clean_init(t_to_clean *clean, char **env, char *line);
int			manage_open_r(t_command **all_cmd, char *last_redir);
int			manage_check_quote(char *line, t_to_clean *clean);

/* 
------------------ ITOA ------------------
*/
char		*ft_itoa(int n);
int			ft_lennum(int n);

/* 
------------------ IS_DIGIT ------------------
*/
int			is_str_digit(char *str);
int			is_str_digit_special(char *str);

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

void		signal_in_cmd(void);
void		signal_manager2(void);
void		signal_cmd(int sig);

/* 
------------------ EXIT_MALLOC ------------------
*/

char		*exit_expand_node_single(t_to_clean *clean,
				char **env, char *str, char *expanded);
void		*ft_clean_error_malloc(t_to_clean *clean);
int			prio_exit(t_command *all);

/*
---------------DOLLAR NORM-------------
*/

int			find_next_single_block_merde(char *str);
char		*del_dollar(char *str, char *var_name, int len, t_to_clean *clean);
char		*cut_dollar(char *str, t_to_clean *clean);
char		*ft_allocate_dest(char *str, char *status, char *dest,
				t_to_clean *clean);
char		*ft_allocate_itoa(char *status, char *str, char *var_name,
				t_to_clean *clean);
void		replace_interrogation_ter(char *str, char *dest, int *i, int *k);
void		replace_interrogation_bis(char *status, char *dest, int *j, int *k);
char		*replace_interrogation_end(char *str, char *status,
				char *var_name, char *dest);
char		*replace_dollar(char *str, char *var_name, int pos,
				t_to_clean *clean);
char		*del_one_back_slash(char *str, t_to_clean *clean);
int			ft_lstsize_cmd(t_command *lst);
char		*expand_dollar(char **env, char *str, t_to_clean *clean); //change
char		*expand_dollar_bis(char *str, int i, t_to_clean *clean);
void		expand_dollar_ter(char *str, int *i);
void		expand_dollar_quin(char *str, int *i);
char		*expand_dollar_six(char *str, int *i, char *var_name,
				t_to_clean *clean);
char		*cpy_block_special(char	*str, int size, t_to_clean *clean);
char		*ft_allocate_echapment(char *str, char *new, t_to_clean *clean);
int			nb_back_slash(char *str);
char		*expand_node(char *str, t_to_clean *clean);
char		*add_echapment(char *str, t_to_clean *clean);
char		*del_back_slash(char *str, t_to_clean *clean);
char		*expand_node_dollar(char *str, char *block, t_to_clean *clean,
				int *i);
char		*expand_node_d_quote(char *str, char *block, t_to_clean *clean,
				int *i);
char		*expand_node_quote(char *str, char *block, t_to_clean *clean,
				int *i);
char		*ft_allocate_expanded(char *str, char *block, char *expanded,
				t_to_clean *clean);
int			find_next_single_block(char *str);
char		*expand_node_single_quote(char *str, t_to_clean *clean, int *i,
				char *expanded);
char		*expand_node_single_d_quote(char *str, t_to_clean *clean, int *i,
				char *expanded);
char		*expand_node_single_dollar(char *str, t_to_clean *clean, int *i,
				char *expanded);
char		*expand_node_single_backlash(char *str, t_to_clean *clean, int *i,
				char *expanded);
char		*expand_node_single_else(char *str, t_to_clean *clean, int *i,
				char *expanded);
char		**manage_line_bis_2(t_command *cmd_all, t_to_clean *clean,
				char **env, t_token *expanded);
void		manage_line_clean(t_to_clean *clean,
				t_command *cmd_all, t_token *expanded);
int			ft_lstsize_cmd_wesh(t_command *lst);
int			condition_if_exit(t_command *all);
int			ft_lstsize_cmd_pipe(t_command *lst);
void		exit_overflow(char *number, t_to_clean *clean);
void		ft_exit_2(char **full_cmd, t_to_clean *clean);
void		check_if_exit(t_to_clean *clean, t_command *all, t_token *expanded);
int			is_expand_block_node(char *block);
int			ft_isalnum_interogation(int c);
void		dont_expand_special_char(char *str, int *i);
void		ft_memdel(void **ptr);
int			manage_check_cmd_list(t_token *tmp, t_to_clean *clean);
void		del_dollar_2_quin(char *var_name);
char		*expand_single_dollar_diff(char **env, char *str,
				t_to_clean *clean);
char		*replace_interrogation_diff(char *str, int pos, t_to_clean *clean,
				char *var_name);
char		*replace_interrogation_end_diff(char *str, char *status,
				char *var_name, char *dest);

#endif
