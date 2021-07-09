#include "tokenizer.h"

size_t	condition_redirects_1(t_line_n_mask *l_n_m, size_t i, char c)
{
	if (l_n_m->line[i] == c && l_n_m->mask[i] == SPEC_SYMBOL
		&& l_n_m->line[i + 1] != c)
		return (1);
	return (0);
}

size_t	condition_redirects_2(t_line_n_mask *l_n_m, size_t i, char c)
{
	if (l_n_m->line[i] == c && l_n_m->mask[i] == SPEC_SYMBOL
		&& l_n_m->line[i + 1] == c && l_n_m->mask[i + 1] == SPEC_SYMBOL)
		return (1);
	return (0);
}

size_t	condition_redirects3(t_line_n_mask *l_n_m, size_t start)
{
	if (l_n_m->line[start] && ((l_n_m->mask[start] == '1'
				&& !(l_n_m->mask[start] == '1' && l_n_m->line[start] == ' '))
			|| (l_n_m->line[start] == '$')
			|| (l_n_m->mask[start] == UNUSED_BACKSLASH)
			|| (l_n_m->mask[start] == OPEN_QUOTE)
			|| (l_n_m->mask[start] == CLOSE_QUOTE)
			|| (l_n_m->mask[start] == SPACE_VISIBLE)))
		return (1);
	return (0);
}

size_t	condition_cmd_limits(t_line_n_mask *l_n_m, size_t i)
{
	if (l_n_m->line[i] && !(l_n_m->line[i] == '|'
			&& l_n_m->mask[i] == SPEC_SYMBOL)
		&& (l_n_m->mask[i] != CURRENT_SPLIT))
		return (1);
	return (0);
}

size_t	handle_cmd_condition(t_line_n_mask *l_n_m, size_t i)
{
	if (l_n_m->mask[i] == UNUSED_BACKSLASH
		|| l_n_m->mask[i] == CLOSE_QUOTE || l_n_m->mask[i] == UNUSED_SYMBOL
		|| (l_n_m->mask[i] == '1' && l_n_m->line[i] == ' ')
		|| (l_n_m->mask[i] == SPEC_SYMBOL && l_n_m->line[i] != '$'))
		return (1);
	return (0);
}
