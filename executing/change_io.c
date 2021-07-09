#include "executing.h"

void	dup_error(t_line_n_mask *l_n_m)
{
	l_n_m->status = errno;
}

static void	change_first_io(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	int	tmpin;
	int	tmpout;

	tmpin = dup(token->fd_from);
	if (tmpin < 0)
		return (dup_error(l_n_m));
	if (dup2(tmpin, 0) < 0)
		return (dup_error(l_n_m));
	close(tmpin);
	if (i != l_n_m->cnt_pipes)
	{
		tmpout = dup(l_n_m->pipes[i + 1][1]);
		if (tmpout < 0)
			return (dup_error(l_n_m));
		if (token->fd_to != 1)
			tmpout = token->fd_to;
		if (dup2(tmpout, 1) < 0)
			return (dup_error(l_n_m));
		close(tmpout);
	}
}

static void	change_last_io(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	int	tmpin;
	int	tmpout;

	if (i != 0)
	{
		tmpin = dup(l_n_m->pipes[i][0]);
		if (tmpin < 0)
			return (dup_error(l_n_m));
		if (token->fd_from != 0)
			tmpin = token->fd_from;
		if (dup2(tmpin, 0) < 0)
			return (dup_error(l_n_m));
		close(tmpin);
	}
	tmpout = dup(token->fd_to);
	if (tmpout < 0)
		return (dup_error(l_n_m));
	if (dup2(tmpout, 1) < 0)
		return (dup_error(l_n_m));
	close(tmpout);
}

static void	change_inside_io(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	int	tmpin;
	int	tmpout;

	tmpin = dup(l_n_m->pipes[i][0]);
	if (tmpin < 0)
		return (dup_error(l_n_m));
	tmpout = dup(l_n_m->pipes[i + 1][1]);
	if (tmpout < 0)
		return (dup_error(l_n_m));
	if (token->fd_to != 1)
		tmpout = token->fd_to;
	if (token->fd_from)
		tmpin = token->fd_from;
	if (dup2(tmpin, 0) < 0)
		return (dup_error(l_n_m));
	if (dup2(tmpout, 1) < 0)
		return (dup_error(l_n_m));
	close (tmpin);
	close (tmpout);
}

void	change_io(t_line_n_mask *l_n_m, t_token *token, size_t i,
size_t is_child)
{
	size_t	k;

	k = 0;
	if (is_child)
	{
		while (k < l_n_m->cnt_pipes + 1)
		{
			if (i != k)
				close(l_n_m->pipes[k][0]);
			if (i + 1 != k)
				close(l_n_m->pipes[k][1]);
			k++;
		}
	}
	if (i == 0)
		change_first_io(l_n_m, token, i);
	if (i == l_n_m->cnt_pipes)
		change_last_io(l_n_m, token, i);
	if (i != 0 && i != l_n_m->cnt_pipes)
		change_inside_io(l_n_m, token, i);
}
