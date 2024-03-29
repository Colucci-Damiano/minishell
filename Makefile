NAME =		minishell

SRC =		main.c split_quotes.c trim_quotes.c split_command.c  final_split.c ft_gest_ambiental.c ft_gest_ambiental_00.c ft_check_syntax.c \
			ft_create_cmds.c ft_create_node.c ft_create_node_00.c ft_heredoc.c ft_exe.c ft_exe_00.c ft_exe_01.c ft_exe_02.c ft_builtins.c ft_builtins_00.c ft_builtins_01.c ft_signals.c

UTILS =		utils1.c utils2.c utils3.c utils4.c utils1_free.c utils_print.c utils_cmd.c

LIB =		./libft/libft.a
GNL =		./gnl/get_next_line_utils_bonus.c ./gnl/get_next_line_bonus.c

CFLAGS =	-Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(SRC) $(UTILS)
	@make bonus -s -C libft
	@gcc $(SRC) $(UTILS) $(GNL) $(CFLAGS) $(LIB) -o $(NAME) -lreadline

clean:
	@make clean -s -C libft

fclean:
	@make fclean -s -C libft
	@rm -f $(NAME)

re: fclean all
