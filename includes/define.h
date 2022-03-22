#ifndef DEFINE_H
# define DEFINE_H

# define BUFFER_SIZE 2048
# define FALSE 1
# define TRUE 0

# define PIPE 1
# define CHV_R 2
# define CHV_L 3
# define D_CHV_R 4
# define D_CHV_L 5
# define WORD 6
# define QUOTE '\''
# define D_QUOTE '\"'
# define BACK_SLASH 92

# define FT_CD 1
# define FT_PWD 2
# define FT_ENV 3
# define FT_UNSET 4
# define FT_EXPORT 5
# define FT_ECHO 6
# define FT_EXIT 7

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>

extern int	g_status;

#endif
