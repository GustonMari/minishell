NAME = minishell
CLEANHEREDOC = srcs/heredoc/clean_heredoc

LIBINC = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

SRCDIR = srcs
OBJDIR = objs
INCDIR = includes

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MEM =  #-fsanitize=address

ifeq ($(TMEM),0)
MEM =
endif

INC = 	colors.h \
		define.h \
		function.h \
		struct.h

SRC =	srcs/main.c \
		srcs/builtin/echo.c \
  		srcs/builtin/env.c \
		srcs/builtin/exit.c \
		srcs/builtin/exit_2.c \
		srcs/builtin/export_2.c \
		srcs/builtin/export_3.c \
		srcs/builtin/export.c \
		srcs/builtin/ft_cd.c \
		srcs/builtin/pwd.c \
		srcs/builtin/unset.c \
		srcs/builtin/unset_2.c \
		srcs/builtin/manage_export.c \
		srcs/builtin/export_no_arg.c \
		srcs/check/check.c \
		srcs/check/check_op.c \
		srcs/check/quote.c \
		srcs/error/error.c \
		srcs/exec/exec.c \
		srcs/exec/exec_one.c \
		srcs/exec/exec_2.c \
		srcs/exec/exec_cmd.c \
		srcs/expand_new/dollars_6.c \
		srcs/expand_new/dollars_5.c \
		srcs/expand_new/dollars_4.c \
		srcs/expand_new/dollars_3.c \
		srcs/expand_new/dollars_2.c \
		srcs/expand_new/dollars.c \
		srcs/expand_new/manage_expand_5.c \
		srcs/expand_new/manage_expand_4.c \
		srcs/expand_new/manage_expand_3.c \
		srcs/expand_new/manage_expand_2.c \
		srcs/expand_new/manage_expand.c \
		srcs/expand_new/manage_expand_single_2.c \
		srcs/expand_new/manage_expand_single_3.c \
		srcs/expand_new/manage_expand_single.c \
		srcs/heredoc/heredoc_2.c \
		srcs/heredoc/heredoc.c \
		srcs/heredoc/heredoc_utils.c \
		srcs/heredoc/heredoc_utils_2.c \
		srcs/heredoc/signal_heredoc.c \
		srcs/heredoc/heredoc_bis_2.c \
		srcs/heredoc/heredoc_bis.c \
		srcs/lexer/lexer.c \
		srcs/lexer/remix_lexer_2.c \
		srcs/lexer/remix_lexer.c \
		srcs/manager/dispatch_cmd.c \
		srcs/manager/manager.c \
		srcs/manager/clean_init.c \
		srcs/manager/manager_2.c \
		srcs/manager/remix_2.c \
		srcs/parsing/ft_split_special.c \
		srcs/parsing/token_to_cmd_2.c \
		srcs/parsing/token_to_cmd.c \
		srcs/pipe/pipe_2.c \
		srcs/pipe/pipe.c \
		srcs/pipe/wait.c \
		srcs/redir_test/redirection_manager.c \
		srcs/redir_test/redirection_test_left.c \
		srcs/redir_test/redirection_test_right.c \
		srcs/redir_test/redirection_test_right_2.c \
		srcs/signals/signals.c \
		srcs/utils/clear.c \
		srcs/utils/env_utils.c \
		srcs/utils/ft_atoi.c \
		srcs/utils/ft_isdigit.c \
		srcs/utils/ft_split.c \
		srcs/utils/ft_strtrim.c \
		srcs/utils/shell_lvl.c \
		srcs/utils/env_utils_2.c \
		srcs/utils/export_utils.c \
		srcs/utils/ft_calloc.c \
		srcs/utils/ft_itoa.c \
		srcs/utils/ft_strrchr.c \
		srcs/utils/list_utils.c \
		srcs/utils/utils_1.c \
		srcs/utils/utils_2.c \
		srcs/utils/utils_3.c \
		srcs/utils/utils_4.c \
		srcs/utils/utils_5.c \
		srcs/utils/ft_atol.c \
		srcs/clean_malloc/clean_malloc_1.c

OBJS = $(addprefix ${OBJDIR}/,${SRC:.c=.o})

all: ${NAME} ${CLEANHEREDOC}

RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
CYAN="\033[1;36m"
GREY="\033[0;37m"
RESET="\033[m"

$(NAME): ${OBJS}
#	@echo "\\n\033[32;1mMAKE ALL OK \033[0m \\n"
#	@echo ${GREEN} "           _       _     _          _ _ " ${RESET}
#	@echo ${GREEN} "          (_)     (_)   | |        | | |" ${RESET}
#	@echo ${GREEN} " _ __ ___  _ _ __  _ ___| |__   ___| | |" ${RESET}
##	@echo ${GREEN} "| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |" ${RESET}
#	@echo ${GREEN} "| | | | | | | | | | \\__ \\ | | |  __/ | |" ${RESET}
#	@echo ${GREEN} "|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|" ${RESET}
#	@echo
	${CC} ${CFLAGS} ${MEM} ${OBJS} -I./${INCDIR} -o $@ ${LIBINC}

$(CLEANHEREDOC):
	${CC} ${CFLAGS} srcs/heredoc/clean_heredoc.c -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} ${MEM} -I./${INCDIR} -c $< -o $@

re: fclean all

clean:
	@echo  "Cleaning objects\c"
	@rm -rf ${OBJDIR}
	@echo "\033[32m\t[OK]\033[0m"

fclean: clean
	@echo  "Removing minishell\c"
	@rm -rf ${NAME} ${CLEANHEREDOC}
	@echo "\033[32m\t[OK]\033[0m"

.PHONY : all clean re fclean 
