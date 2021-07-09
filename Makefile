NAME = minishell

CC = gcc

INCLUDES = builtins/builtins.h executing/executing.h minishell_utils/minishell_utils.h parser/parser.h \
			termcap/termcap.h tokenizer/tokenizer.h minishell.h

CFLAGS = -Wall -Wextra -Werror

BUILTINS = cd_utils check_export echo env env_alpha exit export export_utills is_builtin manage_duplications \
			pwd_cd unset

EXECUTING = change_io child_process executing executing_utils free_functions waiting_childs

MINISHELL_UTILS = ft_itoa ft_split memory_handle_utils string_utils1 string_utils2 string_utils3 string_utils4

PARSER = backslash parser quotes_handler redirects_syntax syntax_err

TERMCAP = check_for_exit keys keys2 term_utills

TOKENIZER = check_cmd check_directory cmd conditions conditions_utils dollar_sign_assign dollar_sign_cnt \
			free_and_exit_tokenizer get_redirect redirect_error redirects

SRC = $(addsuffix .c, $(addprefix builtins/, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix executing/, $(EXECUTING))) \
		$(addsuffix .c, $(addprefix minishell_utils/, $(MINISHELL_UTILS))) \
		$(addsuffix .c, $(addprefix parser/, $(PARSER))) \
		$(addsuffix .c, $(addprefix termcap/, $(TERMCAP))) \
		$(addsuffix .c, $(addprefix tokenizer/, $(TOKENIZER))) \
		main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDES)
		 $(CC) $(CFLAGS) -ltermcap $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

norm:
	norminette $(SRC) $(INCLUDES)