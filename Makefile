CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = colors.c \
			ft_gustave.c \
			ft_julia.c \
			ft_key.c \
			ft_mandelbrot.c \
			ft_zoom.c \
			main.c
OBJ = $(SRC:.c=.o)
NAME= fractol

all: server
	@echo "\\n\033[32;1mMAKE ALL OK \033[0m \\n"
	@echo "\033[32;1m            _       _     _          _ _  \033[0m"
	@echo "\033[32;1m           (_)     (_)   | |        | | | \033[0m"
	@echo "\033[32;1m  _ __ ___  _ _ __  _ ___| |__   ___| | | \033[0m"
	@echo "\033[32;1m | '_ ` _ \| | '_ \| / __| '_ \ / _ \ | | \033[0m"
	@echo "\033[32;1m | | | | | | | | | | \__ \ | | |  __/ | | \033[0m"
	@echo "\033[32;1m |_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_| \033[0m"
	@echo "\\n"

server: $(NAME)

$(NAME): $(OBJ)
	make -C minilibx_linux
	$(CC) -o $(NAME) $(OBJ) -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
	@echo "\\n\033[32;1mCOMPILATION OK \033[0m \\n"

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	@echo "\\n\033[38;5;202;1mDeleting Objects... \033[0m \\n"
	rm -rf $(OBJ)
	make -C minilibx_linux clean
	@echo "\\n\033[32;1mDeleting OK \033[0m \\n"

fclean: clean
	@echo "\\n\033[38;5;202;1mCLEANING ALL... \033[0m \\n"
	make -C minilibx_linux clean
	rm -rf $(NAME)
	@echo "\\n\033[32;1mOK \033[0m \\n"

re: fclean all

.PHONY: all clean fclean re libft server client

.SILENT:
