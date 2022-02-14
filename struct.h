/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:00:55 by gmary             #+#    #+#             */
/*   Updated: 2022/02/14 18:01:33 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_tokentype
{
	NO_QUOTE,
	QUOTE,
	DQUOTE,
	CMD,
	DOLLAR,
	WORD,
	SPACE,
	NO_NEW_LINE //pour le -n de echo
}	t_tokentype;

typedef struct t_token
{
	t_tokentype	type;
	char		*value;
	struct t_token		*next;
}				s_token;


#endif