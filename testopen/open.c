/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 07:43:18 by gmary             #+#    #+#             */
/*   Updated: 2022/02/11 14:24:07 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "function.h"

/*
	OPENDIR:
	-prend le non du dossier ou le path
	-si opendir retourne NULL cest que louverture a echoue sinon pointeur sur la struct DIR
	READDIR:
	-prend le non du dossier ou path
	- retourn un pt sur la struct dirent, retourne NULL en fin de dossier parfait pour la lecture tel que:
	
	while ((pDirent = readdir(pDir)) != NULL)
		printf ("[%s]\n", pDirent->d_name);

*/

int main(void)
{
	struct dirent *pdirent;
	DIR *pdir;

	pdir = opendir("testopen");
	if (pdir == NULL)
	{
		printf("open failed\n");
		exit(EXIT_FAILURE);
	}
	printf("getenv %s\n", getenv("PWD"));
	while ((pdirent = readdir(pdir)) != NULL)
		printf("%s\n", pdirent->d_name);
	closedir(pdir);
	return (0);
}