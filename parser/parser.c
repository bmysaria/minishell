#include "parser.h"

static void	move_spaces(const char *line, const char *mask,
size_t *j, size_t *k)
{
	while (line[*j] && line[*j] == ' ' && mask[*j] == '1')
		(*j)++;
	while (*k >= 0 && line[*k] == ' ' && mask[*k] == '1')
		(*k)--;
}

static size_t	pipe_syntax(const char *line, const char *mask, char *c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	*c = '|';
	i = 0;
	while (i < ft_strlen(line))
	{
		if ((i == ft_strlen(line) - 1 || i == 0) && line[i] == '|'
			&& mask[i] == SPEC_SYMBOL)
			return (0);
		if (line[i] == '|' && mask[i] == SPEC_SYMBOL)
		{
			k = i - 1;
			j = i + 1;
			move_spaces(line, mask, &j, &k);
			if (!mask[j] || (mask[j] == SPEC_SYMBOL && line[j] != '$')
				|| (mask[k] == SPEC_SYMBOL && line[k] != '$'))
				return (0);
		}
		i++;
	}
	return (1);
}

static size_t	semicolon_syntax(const char *line, const char *mask, char *c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	*c = ';';
	i = 0;
	while (i < ft_strlen(line))
	{
		if (i == 0 && line[i] == ';' && mask[i] == SPEC_SYMBOL)
			return (0);
		if (line[i] == ';' && mask[i] == SPEC_SYMBOL)
		{
			k = i - 1;
			j = i + 1;
			move_spaces(line, mask, &j, &k);
			if ((mask[j] == SPEC_SYMBOL && line[j] != '$')
				|| (mask[k] == SPEC_SYMBOL && line[k] != '$'))
				return (0);
		}
		i++;
	}
	return (1);
}

int	parser(const char *line, const char *mask)
{
	char	c;

	if (!redirect_syntax(line, mask, &c))
	{
		print_syntax_err(c);
		return (0);
	}
	if (!pipe_syntax(line, mask, &c))
	{
		print_syntax_err(c);
		return (0);
	}
	if (!semicolon_syntax(line, mask, &c))
	{
		print_syntax_err(c);
		return (0);
	}
	return (1);
}
