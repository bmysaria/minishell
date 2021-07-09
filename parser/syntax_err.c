#include "parser.h"

void	print_syntax_err(char err)
{
	write(2, SYNTAX_ERR, ft_strlen(SYNTAX_ERR));
	write(2, &err, 1);
	write(2, "\n", 1);
}
