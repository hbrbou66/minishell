NAME = minishell

CC = cc
RM = rm -rf

BREW_PATH = /opt/homebrew/opt/readline
CFLAGS = -Wall -Wextra -Werror -I$(BREW_PATH)/include
RDFLAGS = -L$(BREW_PATH)/lib -lreadline

SRC = minishell.c \
	utils/ft_strlen.c parse/ft_check_quots.c parse/ft_parse_command.c \
	utils/ft_strjoin.c utils/ft_lst_utils.c utils/ft_syntax_error.c \
	parse/ft_split_command.c parse/ft_token_type.c utils/ft_substr.c \
	utils/ft_is_space.c utils/ft_split.c utils/ft_strchr.c \
	utils/ft_strdup.c utils/ft_strlcpy.c memory.c parse/ft_quotes_type.c \
	parse/ft_expend.c utils/ft_strlcat.c exec/exec_main.c exec/exec_child.c \
	exec/builtins.c exec/exec_list.c exec/exec_more_list.c exec/parse_to_exec.c \
	exec/exec_utils.c exec/export.c exec/unset.c exec/echo.c exec/env.c \
	exec/cd.c exec/ft_split_exec.c parse/ft_redirection_operators.c \
	utils/ft_strcomp.c exec/exit.c exec/ft_itoa_atoi.c exec/pwd.c \
	exec/export_more.c exec/parse_to_exec_more.c exec/find_cmd_path.c \
	parse/ft_expand_value.c parse/ft_check_bracets.c parse/ft_remove_bracets.c \
	parse/ft_logic_syntax.c utils/ft_isalpha.c parse/ft_getenv.c \
	utils/split_expn.c utils/ft_acctual_split.c utils/split_var.c \
	parse/skip_till_pipe.c

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(RDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re