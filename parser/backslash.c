#include "parser.h"

static void	fake_and_space(char *line, char *mask, size_t *i)
{
	mask[*i] = UNUSED_BACKSLASH;
	if (ft_strchr("<>|;$'", line[*i + 1]))
		mask[*i + 1] = FAKE_SPEC_SYMBOL;
	else if (line[*i + 1] == ' ')
		mask[*i + 1] = SPACE_VISIBLE;
	(*i) += 2;
}

static void	loop_quotes(char *mask, size_t *i)
{
	while (mask[++(*i)] != CLOSE_QUOTE)
		;
	(*i)++;
}

static void	mask_handler_normal(char *line, char *mask)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (mask[i] == OPEN_QUOTE)
			loop_quotes(mask, &i);
		else if (line[i] && line[i] == 92 && line[i + 1]
			&& (ft_strchr("<>|;$'\" ", line[i + 1])))
			fake_and_space(line, mask, &i);
		else if (line[i] && ((line[i] == 92 && line[i + 1] && line[i + 1] == 92)
				|| (line[i] == 92 && !line[i + 1])))
		{
			mask[i] = UNUSED_BACKSLASH;
			i += 2;
		}
		else if (line[i] && line[i] == 92 && line[i + 1]
			&& (!ft_strchr("<>|;$'\"", line[i + 1])))
			mask[i++] = UNUSED_BACKSLASH;
		else if (line[i] && (ft_strchr("<>|;$", line[i])) && mask[i] == '1')
			mask[i++] = SPEC_SYMBOL;
		else
			i++;
	}
}

static void	mask_handler_real(char *line, char *mask)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (mask[i] == OPEN_QUOTE)
		{
			while (mask[++i] != CLOSE_QUOTE)
				;
			i++;
		}
		else if (ft_strchr("<>|;$", line[i]))
			mask[i++] = SPEC_SYMBOL;
		else
			i++;
	}
}

size_t	get_mask_normal(char *line, char *mask)
{
	if (!quotes_handler(line, mask))
	{
		write(2, "syntax error with quotes\n",
			ft_strlen("syntax error with quotes\n"));
		free(mask);
		return (0);
	}
	mask_handler_real(line, mask);
	mask_handler_normal(line, mask);
	return (1);
}
