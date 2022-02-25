/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:00:55 by gmary             #+#    #+#             */
/*   Updated: 2022/02/24 16:06:29 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	t_tokentype	type;
	char		*content;
	struct s_token		*next;
}				t_token;

typedef struct s_command
{
	t_tokentype 	type;
	char		**cmd_to_exec;
	struct s_command	*next;
}				t_command;

#endif