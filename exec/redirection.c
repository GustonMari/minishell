#include "../includes/function.h"

int    ft_redirection_chv_r(char *str)
{
    int fd_file;
	int	fd[2];
	int	pid;

    fd_file = open(str, O_CREAT | O_WRONLY | O_TRUNC, 00666);
	if (fd_file < 0)
	{
		printf("Pb open file\n");
		return (-1);
	}
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if ((pid = fork ()) == 0) 
	{
        if (fd[0] != 0) {
          dup2 (fd[0], 0);
          close (fd[0]);
        }
        if (fd_file != 1) 
		{
          dup2 (fd_file, 1);
          close (fd_file);
        }
	}
    return (0);
}