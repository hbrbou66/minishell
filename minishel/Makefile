NAME = minishell

CC = cc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror
RDFLAGS = -lreadline

SRC = minishell.c \
	utils/ft_strlen.c parse/ft_check_quots.c parse/ft_command_parse.c \
	utils/ft_strjoin.c utils/ft_lst_utils.c utils/ft_syntax_error.c \
	parse/ft_split_command.c parse/ft_type_token.c utils/ft_substr.c \
	utils/ft_is_space.c utils/ft_split.c utils/ft_strchr.c \
	utils/ft_strdup.c utils/ft_strlcpy.c memory.c parse/ft_quote_types.c \
	parse/ft_expend.c utils/ft_strlcat.c exec/main_exec.c exec/child_exec.c \
	exec/ft_is_builtins.c exec/list_exec.c exec/exec_list_more.c exec/parse_exec.c \
	exec/exec_util.c exec/ft_export.c exec/ft_unset.c exec/ft_echo.c exec/ft_env.c \
	exec/ft_cd.c exec/ft_exec_split.c parse/ft_operators_redirection.c \
	utils/ft_strcomp.c exec/ft_exit.c exec/ft_iatoa.c exec/ft_pwd.c \
	exec/ft_export_more.c exec/parse_exec_more.c exec/find_path_cmd.c exec/execve_error.c \
	parse/ft_expand_value.c parse/ft_bracets_check.c parse/ft_bracets_remove.c \
	parse/ft_syntax_logic.c utils/ft_isalpha.c parse/ft_get_env.c utils/ft_calloc.c \
	utils/split_expn.c utils/ft_acctual_split.c utils/split_var.c parse/skip_till_pipe.c

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
