#include "executing.h"

t_token	token_init(void)
{
	return ((t_token){
		.args = 0,
		.lower = 0,
		.line = 0,
		.fd_from = 0,
		.fd_to = 1
	});
}

t_line_n_mask	struct_init(char ***env, char *mask, t_gnl *gnl, char *str)
{
	return ((t_line_n_mask){
		.line = str,
		.env = env,
		.mask = mask,
		.free_line = 0,
		.pipes = 0,
		.pids = 0,
		.status = gnl->status,
		.cnt_pipes = 0,
		.gnl = gnl
	});
}

void	free_token(t_token *token)
{
	size_t	i;

	i = 0;
	if (token->args)
	{
		while (token->args[i])
			free(token->args[i++]);
		free(token->args);
	}
	if (token->line)
		free(token->line);
	if (token->fd_from > 0)
		close(token->fd_from);
	if (token->fd_to > 1)
		close(token->fd_to);
	if (token->lower)
		free(token->lower);
}

size_t	get_next_pipe(t_line_n_mask *l_n_m, size_t j)
{
	while (l_n_m->line[j] && !(l_n_m->line[j] == '|'
			&& l_n_m->mask[j] == SPEC_SYMBOL))
		j++;
	j++;
	return (j);
}

void	malloc_pipes(t_line_n_mask *l_n_m)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < l_n_m->cnt_pipes + 1)
	{
		l_n_m->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!l_n_m->pipes[i])
		{
			j = 0;
			while (j < i)
				free(l_n_m->pipes[j++]);
			free_and_exit(l_n_m);
		}
		if (pipe(l_n_m->pipes[i]) < 0)
		{
			j = 0;
			while (j < i)
				free(l_n_m->pipes[j++]);
			free_and_exit(l_n_m);
		}
		i++;
	}
}
