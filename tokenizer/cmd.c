#include "tokenizer.h"

static void	get_cnt_to_next_arg(t_line_n_mask *l_n_m, size_t *i)
{
	if (l_n_m->mask[*i] == OPEN_QUOTE)
		(*i)++;
	while (condition_cmd_limits(l_n_m, *i)
		&& !(l_n_m->line[*i] == ' ' && l_n_m->mask[*i] == '1')
		&& !(l_n_m->mask[*i] == SPEC_SYMBOL && l_n_m->line[*i] != '$')
		&& l_n_m->mask[*i] != CLOSE_QUOTE)
		(*i)++;
}

static size_t	get_cnt_cmds(t_line_n_mask *l_n_m, size_t i)
{
	size_t	cnt;

	cnt = 0;
	while (condition_cmd_limits(l_n_m, i))
	{
		if (l_n_m->mask[i] == UNUSED_BACKSLASH
			|| l_n_m->mask[i] == CLOSE_QUOTE || l_n_m->mask[i] == UNUSED_SYMBOL
			|| (l_n_m->mask[i] == '1' && l_n_m->line[i] == ' ')
			|| (l_n_m->mask[i] == SPEC_SYMBOL && l_n_m->line[i] != '$'))
			i++;
		else if ((!(l_n_m->line[i] == ' ' && l_n_m->mask[i] == '1')
				&& !(l_n_m->mask[i] == SPEC_SYMBOL && l_n_m->line[i] != '$'))
			|| l_n_m->mask[i] == OPEN_QUOTE)
		{
			get_cnt_to_next_arg(l_n_m, &i);
			cnt++;
		}
	}
	return (cnt);
}

static void	assign_cmd(t_line_n_mask *l_n_m, char **line, size_t *i, size_t j)
{
	size_t	k;

	k = 0;
	while (*i < j)
	{
		if (l_n_m->mask[*i] == SPEC_SYMBOL && l_n_m->line[*i] == '$')
			handle_string_dollar(l_n_m, *line, i, &k);
		else if (l_n_m->mask[(*i)] != UNUSED_BACKSLASH
			&& l_n_m->mask[(*i)] != OPEN_QUOTE
			&& l_n_m->mask[(*i)] != CLOSE_QUOTE)
			(*line)[k++] = l_n_m->line[(*i)++];
		else
			(*i)++;
	}
	(*line)[k] = '\0';
}

static void	get_size_to_next_arg(t_line_n_mask *l_n_m, size_t *i,
size_t *cnt_symbols, size_t cur)
{
	*i = cur;
	if (l_n_m->mask[*i] == OPEN_QUOTE)
		(*i)++;
	*cnt_symbols = 0;
	while (condition_cmd_limits(l_n_m, *i)
		   && !(l_n_m->line[*i] == ' ' && l_n_m->mask[*i] == '1')
		   && !(l_n_m->mask[*i] == SPEC_SYMBOL && l_n_m->line[*i] != '$'))
	{
		if (l_n_m->line[*i] == '$' && l_n_m->mask[*i] == SPEC_SYMBOL)
			(*cnt_symbols) += get_cnt_dollar(l_n_m, i);
		else if (l_n_m->mask[*i] != UNUSED_BACKSLASH
			&& l_n_m->mask[*i] != OPEN_QUOTE && l_n_m->mask[*i] != CLOSE_QUOTE)
		{
			(*cnt_symbols)++;
			(*i)++;
		}
		else
			(*i)++;
	}
}

void	handle_cmd(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	size_t	cnt;
	size_t	j_end;
	size_t	k;
	size_t	cnt_symbols;

	k = 0;
	j_end = 0;
	cnt = get_cnt_cmds(l_n_m, i);
	token->args = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!token->args)
		free_and_exit_tokenizer(l_n_m);
	while (k < cnt && condition_cmd_limits(l_n_m, i))
	{
		if (handle_cmd_condition(l_n_m, i))
			i++;
		else if (condition_cmd(l_n_m, i))
		{
			get_size_to_next_arg(l_n_m, &j_end, &cnt_symbols, i);
			(token->args)[k] = (char *) malloc(sizeof(char) * cnt_symbols + 1);
			if (!token->args[k])
				free_and_exit_tokenizer_cmd(token, l_n_m, k);
			assign_cmd(l_n_m, &((token->args)[k++]), &i, j_end);
		}
	}
	token->args[k] = 0;
}
