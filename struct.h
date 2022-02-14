/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:00:55 by gmary             #+#    #+#             */
/*   Updated: 2022/02/14 19:24:32 by gmary            ###   ########.fr       */
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

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
	struct s_token		*next;
}				s_token;

typedef struct s_env
{
	char			*str_env;
	struct s_env	*next;
}				t_env;


#endif