/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:00:55 by gmary             #+#    #+#             */
/*   Updated: 2022/02/22 11:51:51 by gmary            ###   ########.fr       */
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

typedef struct s_cmd_line
{
	char				*cmd;
	struct	t_token		*word;
	struct	s_cmd_line	*next;
	
}			t_cmd_line;

#endif