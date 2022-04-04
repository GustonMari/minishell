/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:00:55 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 16:31:17 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_tokentype
{
	PIPE,
	CHV_R,
	CHV_L,
	D_CHV_R,
	D_CHV_L,
	WORD,
	NUL,
}	t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_command
{
	t_tokentype			type;
	int					to_del;
	char				**cmd_to_exec;
	struct s_command	*next;
}				t_command;

typedef struct s_to_clean
{
	t_token		*token_begin;
	t_command	*command_begin;
	char		**env;
	int			not_expand;
}				t_to_clean;

#endif