#include "tokenizer.h"

void	handle_current_redirect_to(t_line_n_mask *l_n_m, t_token *token,
size_t start, size_t cnt)
{
	size_t	j;

	j = 0;
	if (token->fd_to > 1)
		close(token->fd_to);
	if (cnt == 1)
		token->fd_to = open(get_redir(l_n_m, start, &(token->line), j), O_RDWR
				| O_CREAT | O_TRUNC, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
	else
		token->fd_to = open(get_redir(l_n_m, start, &(token->line), j),
				O_RDWR | O_APPEND | O_CREAT, S_IREAD | S_IWRITE | S_IRGRP
				| S_IROTH);
}

void	handle_current_redirect_from(t_line_n_mask *l_n_m, t_token *token,
size_t start)
{
	size_t	j;

	j = 0;
	if (token->fd_from > 0)
		close(token->fd_from);
	token->fd_from = open(get_redir(l_n_m, start, &(token->line), j),
			O_RDONLY);
}

size_t	handle_redirects(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	while (l_n_m->line[i] && !(l_n_m->line[i] == '|'
			&& l_n_m->mask[i] == SPEC_SYMBOL)
		&& (l_n_m->mask[i] != CURRENT_SPLIT))
	{
		if (condition_redirects_1(l_n_m, i, '<'))
			handle_current_redirect_from(l_n_m, token, i + 1);
		else if (condition_redirects_2(l_n_m, i, '<'))
		{
			handle_current_redirect_from(l_n_m, token, i + 2);
			i++;
		}
		else if (condition_redirects_1(l_n_m, i, '>'))
			handle_current_redirect_to(l_n_m, token, i + 1, 1);
		else if (condition_redirects_2(l_n_m, i, '>'))
		{
			handle_current_redirect_to(l_n_m, token, i + 2, 2);
			i++;
		}
		if (!redirect_error(token, l_n_m))
			return (0);
		i++;
	}
	return (1);
}
