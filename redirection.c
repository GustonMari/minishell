#include "function.h"
/*
	O_TRUNC permet de erase tt le fichier 

		wait(&status);
		if (WIFEXITED(status))
		{
			printf("child return status : %d\n", WEXITSTATUS(status));
		}
*/


int	redirection_to_file(char *file_name, char *str)
{
	int	file;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 00644);
		if (file == -1)
		{
			perror("\e[0;31mbash: txt.txt");
			ft_putstr_fd("\e[0m", 2);
			exit (1);
		}
		if(dup2(file, STDOUT_FILENO) == -1)
			return (-1);
		close(file);
		write(STDOUT_FILENO, str, strlen(str));
		exit(5);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

/*
int	main(void)
{
	redirection_to_file("txt.txt", "lolilol");
	write(1, "bjr\n", 4);
	//fputs("salut\n", stdout);
	return (0);
}
*/