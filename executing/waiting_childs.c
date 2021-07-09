#include "executing.h"

static void	last_pid(t_line_n_mask *l_n_m, size_t i, size_t *fl)
{
	waitpid(l_n_m->pids[i], &l_n_m->status, WUNTRACED);
	if (WIFEXITED(l_n_m->status))
		l_n_m->status = WEXITSTATUS(l_n_m->status);
	else if (WIFSIGNALED(l_n_m->status))
	{
		if (!(*fl))
			write(1, "\n", 1);
		l_n_m->status = 128 + WTERMSIG(l_n_m->status);
	}
	else if (WIFSTOPPED(l_n_m->status))
	{
		if (!(*fl))
			write(1, "\n", 1);
		l_n_m->status = 128 + WSTOPSIG(l_n_m->status);
	}
}

static void	average_pid(t_line_n_mask *l_n_m, size_t i, size_t *fl)
{
	int	temp_stat;

	waitpid(l_n_m->pids[i], &temp_stat, 0);
	if (WIFSIGNALED(temp_stat))
	{
		if (!(*fl))
		{
			write(1, "\n", 1);
			*fl = 1;
		}
		temp_stat = 128 + WTERMSIG(temp_stat);
	}
	else if (WIFSTOPPED(temp_stat))
	{
		if (!(*fl))
		{
			write(1, "\n", 1);
			*fl = 1;
		}
		temp_stat = 128 + WSTOPSIG(temp_stat);
	}
}

void	wait_childs(t_line_n_mask *l_n_m)
{
	size_t	i;
	size_t	fl;

	i = 0;
	fl = 0;
	while (i < l_n_m->cnt_pipes + 1)
	{
		if (l_n_m->pids[i] != -1)
		{
			if (i == l_n_m->cnt_pipes)
				last_pid(l_n_m, i, &fl);
			else
				average_pid(l_n_m, i, &fl);
		}
		i++;
	}
}
