#include "executing.h"

static size_t	handle_pipes(t_line_n_mask *l_n_m, size_t i)
{
	size_t	start;

	start = i;
	l_n_m->cnt_pipes = 0;
	while (l_n_m->line[i] && l_n_m->mask[i] != CURRENT_SPLIT)
	{
		if (l_n_m->line[i] == '|' && l_n_m->mask[i] == SPEC_SYMBOL)
			l_n_m->cnt_pipes++;
		i++;
	}
	l_n_m->pipes = (int **)malloc(sizeof(int *) * (l_n_m->cnt_pipes + 1));
	if (!l_n_m->pipes)
		free_and_exit(l_n_m);
	malloc_pipes(l_n_m);
	l_n_m->pids = (int *)malloc(sizeof(int) * (l_n_m->cnt_pipes + 1));
	if (!l_n_m->pids)
		free_and_exit(l_n_m);
	i = 0;
	while (i < l_n_m->cnt_pipes + 1)
		l_n_m->pids[i++] = -1;
	i = start;
	kernel_start(l_n_m, i);
	l_n_m->gnl->status = l_n_m->status;
	free_kernel(l_n_m);
	return (0);
}

static void	check_last_pipe(t_line_n_mask *l_n_m, size_t j)
{
	size_t	i;

	i = j;
	while (l_n_m->line[i])
	{
		if (!(l_n_m->line[i] == ' ' && l_n_m->mask[i] == '1'))
		{
			handle_pipes(l_n_m, j);
			break ;
		}
		i++;
	}
}

static void	delete_unused_dollars_handle(t_line_n_mask *l_n_m, size_t *i)
{
	size_t	cnt;
	size_t	start;

	start = *i;
	cnt = get_cnt_dollar(l_n_m, &start);
	if (!cnt && l_n_m->line[(*i) + 1] && !is_digit(l_n_m->line[(*i) + 1]))
	{
		while (*i < start)
		{
			l_n_m->line[*i] = ' ';
			l_n_m->mask[*i] = '1';
			(*i)++;
		}
	}
	else
		(*i)++;
}

static void	delete_unused_dollars(t_line_n_mask *l_n_m, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j && i < ft_strlen(l_n_m->line))
	{
		if (l_n_m->mask[i] == OPEN_QUOTE)
			while (l_n_m->mask[i++] != CLOSE_QUOTE)
				;
		else if (l_n_m->line[i] == '$' && l_n_m->mask[i] == SPEC_SYMBOL)
			delete_unused_dollars_handle(l_n_m, &i);
		else
			i++;
	}
}

void	handle_semicolons(t_gnl *gnl, char *mask, char ***env)
{
	size_t			i;
	size_t			j;
	t_line_n_mask	l_n_m;
	char			*str;

	i = 0;
	j = 0;
	str = ft_strdup(gnl->history->line);
	l_n_m = struct_init(env, mask, gnl, str);
	if (!str)
		free_and_exit(&l_n_m);
	while (l_n_m.line[i])
	{
		if (l_n_m.line[i] == ';' && mask[i] == SPEC_SYMBOL)
		{
			mask[i] = CURRENT_SPLIT;
			delete_unused_dollars(&l_n_m, i);
			handle_pipes(&l_n_m, j);
			j = i + 1;
		}
		i++;
	}
	check_last_pipe(&l_n_m, j);
	free(str);
}
