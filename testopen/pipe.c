/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:42:35 by gmary             #+#    #+#             */
/*   Updated: 2022/02/11 07:17:10 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "function.h"

#include <stdio.h>
  #include <memory.h>
  #include <unistd.h>
 
  int main( int argc, char ** argv )
  {
       (void)argc;
	   (void)argv;
   /* create the pipe */
   int pfd[2];
   if (pipe(pfd) == -1)
     {
       printf("pipe failed\n");
       return 1;
     }
 
   /* create the child */
   int pid;
   if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 2;
     }
 
   if (pid == 0)
     {
       /* child */
       close(pfd[1]); /* close the unused write side */
       dup2(pfd[0], 0); /* connect the read side with stdin */
       close(pfd[0]); /* close the read side */
       /* execute the process (wc command) */
       execlp("wc", "wc", (char *) 0);
       printf("wc failed"); /* if execlp returns, it's an error */
       return 3;
     }
   else
     {
       /* parent */
       close(pfd[0]); /* close the unused read side */
       dup2(pfd[1], 1); /* connect the write side with stdout */
       close(pfd[1]); /* close the write side */
       /* execute the process (ls command) */
       execlp("ls", "ls", (char *)0);
       printf("ls failed"); /* if execlp returns, it's an error */
       return 4;
     }
   return 0;
  }