/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:42:35 by gmary             #+#    #+#             */
/*   Updated: 2022/02/10 17:05:00 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "function.h"

#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    assert(argc == 2);

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Le fils lit dans le tube */
        close(pipefd[1]);  /* Ferme l'extrémité d'écriture inutilisée */

        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "XXX\n", 4);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } 
	else {                    /* Le père écrit argv[1] dans le tube */
        close(pipefd[0]);       /* Ferme l'extrémité de lecture inutilisée */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);       /* Le lecteur verra EOF */
        wait(NULL);             /* Attente du fils */
        exit(EXIT_SUCCESS);
    }
}
