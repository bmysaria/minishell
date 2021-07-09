#include "tokenizer.h"

size_t	condition_cmd(t_line_n_mask *l_n_m, size_t i)
{
	if ((!(l_n_m->line[i] == ' ' && l_n_m->mask[i] == '1')
			&& !(l_n_m->mask[i] == SPEC_SYMBOL && l_n_m->line[i] != '$'))
		|| (l_n_m->mask[i] == OPEN_QUOTE))
		return (1);
	return (0);
}

size_t 	condition_get_redir_util(t_line_n_mask *l_n_m, size_t start)
{
	if (l_n_m->mask[start] == '1'
		|| l_n_m->mask[start] == SPACE_VISIBLE)
		return (1);
	return (0);
}

size_t	condition_handle_dollar(t_line_n_mask *l_n_m, size_t j)
{
	if (!l_n_m->mask[j] || (!ft_isalpha(l_n_m->line[j])
			&& l_n_m->line[j] != '_' && l_n_m->line[j] != '?'
			&& !is_digit(l_n_m->line[j])))
		return (1);
	return (0);
}

void	body_condition_dollar(t_line_n_mask *l_n_m, char *line, size_t *start,
size_t *i)
{
	if (l_n_m->mask[*start])
		(*start)++;
	line[(*i)++] = '$';
}

void	body_condition_digit(t_line_n_mask *l_n_m, size_t *start)
{
	if (l_n_m->mask[*start])
		(*start)++;
}
