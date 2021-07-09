#include "parser.h"

static size_t	redirect_syntax_2(const char *line, const char *mask, size_t i)
{
	if (i == ft_strlen(line) - 1 && ((line[i] == '<' && mask[i] == SPEC_SYMBOL)
			|| (line[i] == '>' && mask[i] == SPEC_SYMBOL)))
		return (0);
	if ((line[i] == '<' && mask[i] == SPEC_SYMBOL && line[i + 1]
			&& line[i + 1] == '<' && mask[i + 1] == SPEC_SYMBOL
			&& line[i + 2] && line[i + 2] == '<' && mask[i + 2] == SPEC_SYMBOL)
		|| (line[i] == '>' && mask[i] == SPEC_SYMBOL && line[i + 1]
			&& line[i + 1] == '>' && mask[i + 1] == SPEC_SYMBOL
			&& line[i + 2] && line[i + 2] == '>' && mask[i + 2] == SPEC_SYMBOL))
		return (0);
	if ((line[i] == '<' && mask[i] == SPEC_SYMBOL) || (line[i] == '>'
			&& mask[i] == SPEC_SYMBOL))
	{
		i++;
		while (line[i] && ((line[i] == ' ' && mask[i] == '1')
				|| (mask[i] == UNUSED_BACKSLASH)))
			i++;
		if (!line[i])
			return (0);
	}
	return (1);
}

static size_t	redirect_syntax_1(const char *line, const char *mask, size_t i)
{
	if ((!i && line[i] == '<' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] == '<' && mask[i + 1] == SPEC_SYMBOL
			&& !line[i + 2]) || (!i && line[i] == '<' && mask[i] == SPEC_SYMBOL
			&& !line[i + 1]))
		return (0);
	if ((!i && line[i] == '>' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] == '>' && mask[i + 1] == SPEC_SYMBOL
			 && !line[i + 2]) || (!i && line[i] == '>' && mask[i] == SPEC_SYMBOL
			 && !line[i + 1]))
		return (0);
	if ((line[i] == '<' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] =='>' && mask[i + 1] == SPEC_SYMBOL)
		|| (line[i] == '>' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] == '<' && mask[i + 1] == SPEC_SYMBOL))
		return (0);
	return (1);
}

size_t	redirect_syntax(const char *line, const char *mask, char *c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (!redirect_syntax_1(line, mask, i)
			|| !redirect_syntax_2(line, mask, i))
		{
			*c = line[i];
			return (0);
		}
		i++;
	}
	return (1);
}
