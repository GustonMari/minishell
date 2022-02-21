/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:00:55 by gmary             #+#    #+#             */
/*   Updated: 2022/02/21 09:32:21 by ndormoy          ###   ########.fr       */
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

#endif