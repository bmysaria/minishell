#include "executing.h"

void	free_kernel(t_line_n_mask *l_n_m)
{
	size_t	i;

	i = 0;
	if (l_n_m->pipes)
	{
		while (i < l_n_m->cnt_pipes + 1)
			free(l_n_m->pipes[i++]);
		free(l_n_m->pipes);
		l_n_m->pipes = 0;
	}
	if (l_n_m->pids)
		free(l_n_m->pids);
	l_n_m->pids = 0;
}

void	free_and_exit(t_line_n_mask *l_n_m)
{
	size_t	j;

	j = 0;
	free_gnl(l_n_m->gnl);
	while (l_n_m->env[j])
		free(l_n_m->env[j++]);
	free (l_n_m->env);
	free (l_n_m->mask);
	if (l_n_m->pids)
		free(l_n_m->pids);
	if (l_n_m->pipes)
	{
		j = 0;
		while (j < l_n_m->cnt_pipes + 1)
			free(l_n_m->pipes[j++]);
		free(l_n_m->pipes);
	}
	if (*(l_n_m->free_line))
		free(*(l_n_m->free_line));
	exit (1);
}
