#include "parser.h"

static size_t	single_quotes_handler(char *line, char *mask, size_t *i)
{
	size_t	j;

	mask[*i] = OPEN_QUOTE;
	j = ++(*i);
	while (j < ft_strlen(line) && line[j] != '\'')
		j++;
	if (j == ft_strlen(line))
		return (0);
	while (*i < j)
	{
		if (line[*i] == ' ')
			mask[(*i)++] = SPACE_VISIBLE;
		else
			mask[(*i)++] = '1';
	}
	mask[*i] = CLOSE_QUOTE;
	return (1);
}

static size_t	condition_double_quotes_handler(char *line, size_t j)
{
	if (j < ft_strlen(line) && ((line[j] != '\"')
			|| (line[j] == '\"' && line[j - 1] == '\\'
				&& line[j - 2] != '\\')))
		return (1);
	return (0);
}

static size_t	double_quotes_handler(char *line, char *mask, size_t *i)
{
	size_t	j;

	mask[*i] = OPEN_QUOTE;
	j = ++(*i);
	while (condition_double_quotes_handler(line, j))
		j++;
	if (j == ft_strlen(line))
		return (0);
	while (*i < j)
	{
		if (line[*i] == '\\' && ft_strchr("$\"\\", line[*i + 1]))
		{
			mask[*i] = UNUSED_BACKSLASH;
			mask[(*i) + 1] = '1';
			(*i) += 2;
		}
		else if (line[*i] == '$')
			mask[(*i)++] = SPEC_SYMBOL;
		else if (line[*i] == ' ')
			mask[(*i)++] = SPACE_VISIBLE;
		else
			mask[(*i)++] = '1';
	}
	mask[*i] = CLOSE_QUOTE;
	return (1);
}

size_t	quotes_handler(char *line, char *mask)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if ((i > 0 && ft_strchr("\'\"", line[i]) && (line[i - 1] != '\\'
					|| (line[i - 1] == '\\' && line[i - 2] == '\\')))
			|| (i == 0 && ft_strchr("\'\"", line[i])))
		{
			if ((line[i] == '\'' && !single_quotes_handler(line, mask, &i))
				|| (line[i] == '\"' && !double_quotes_handler(line, mask, &i)))
				return (0);
		}
		i++;
	}
	return (1);
}
