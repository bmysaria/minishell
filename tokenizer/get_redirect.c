#include "tokenizer.h"

static size_t	get_cnt_redirect(t_line_n_mask *l_n_m, size_t start)
{
	size_t	cnt;

	cnt = 0;
	while ((l_n_m->line[start] == ' ' && l_n_m->mask[start] == '1')
		   || (l_n_m->mask[start] == UNUSED_BACKSLASH))
		start++;
	while (condition_redirects3(l_n_m, start))
	{
		if ((l_n_m->line[start] == '\\'
				&& l_n_m->mask[start] == UNUSED_BACKSLASH)
			|| (l_n_m->mask[start] == OPEN_QUOTE)
			|| (l_n_m->mask[start] == CLOSE_QUOTE))
			start++;
		else if (l_n_m->mask[start] == '1'
			|| l_n_m->mask[start] == SPACE_VISIBLE)
		{
			cnt++;
			start++;
		}
		else if (l_n_m->line[start] == '$' && l_n_m->mask[start] == SPEC_SYMBOL)
			cnt += get_cnt_dollar(l_n_m, &start);
	}
	return (cnt);
}

static void	change_mask(t_line_n_mask *l_n_m, size_t j, size_t start, char *s)
{
	while (j < start)
		l_n_m->mask[j++] = UNUSED_SYMBOL;
	*s = '\0';
}

static size_t 	condition_get_redir(t_line_n_mask *l_n_m, size_t start)
{
	if ((l_n_m->line[start] == '\\' && l_n_m->mask[start] == UNUSED_BACKSLASH)
		|| (l_n_m->mask[start] == OPEN_QUOTE)
		|| (l_n_m->mask[start] == CLOSE_QUOTE))
		return (1);
	return (0);
}

char	*get_redir(t_line_n_mask *l_n_m, size_t start, char **line, size_t j)
{
	size_t	cnt;
	size_t	i;

	i = 0;
	j = start;
	if (*line)
		free(*line);
	cnt = get_cnt_redirect(l_n_m, start);
	*line = (char *)malloc(sizeof(char) * cnt + 1);
	if (!(*line))
		free_and_exit_tokenizer(l_n_m);
	while ((l_n_m->line[start] == ' ' && l_n_m->mask[start] == '1')
		   || (l_n_m->mask[start] == UNUSED_BACKSLASH))
		start++;
	while (condition_redirects3(l_n_m, start))
	{
		if (condition_get_redir(l_n_m, start))
			start++;
		else if (condition_get_redir_util(l_n_m, start))
			(*line)[i++] = l_n_m->line[start++];
		else if (l_n_m->line[start] == '$' && l_n_m->mask[start] == SPEC_SYMBOL)
			handle_string_dollar(l_n_m, *line, &start, &i);
	}
	change_mask(l_n_m, j, start, &((*line)[i]));
	return (*line);
}
