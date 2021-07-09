#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include "../minishell_utils/minishell_utils.h"

# define SYNTAX_ERR "syntax error near token "
# define FAKE_SPEC_SYMBOL '1'
# define CURRENT_SPLIT '2'
# define SPEC_SYMBOL '4'
# define UNUSED_BACKSLASH '5'
# define OPEN_QUOTE '6'
# define CLOSE_QUOTE '7'
# define SPACE_VISIBLE '8'
# define UNUSED_SYMBOL '0'

int		parser(const char *line, const char *mask);
size_t	redirect_syntax(const char *line, const char *mask, char *c);
void	print_syntax_err(char err);
size_t	get_mask_normal(char *line, char *mask);
size_t	quotes_handler(char *line, char *mask);

#endif
