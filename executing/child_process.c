#include "executing.h"
#include "../termcap/termcap.h"

static void	child_process(t_line_n_mask *l_n_m, t_token token, size_t i)
{
	change_io(l_n_m, &token, i, 1);
	execve(token.args[0], token.args, *l_n_m->env);
	perror(token.args[0]);
	exit (1);
}

static void	next_iteration(t_line_n_mask *l_n_m, t_token *token, size_t *j,
size_t *i)
{
	free_token(token);
	*j = get_next_pipe(l_n_m, *j);
	(*i)++;
}

static void	kernel(t_line_n_mask *l_n_m, size_t start)
{
	t_token	token;
	size_t	j;
	size_t	i;

	j = start;
	i = 0;
	while (i < l_n_m->cnt_pipes + 1)
	{
		token = token_init();
		if (handle_redirects(l_n_m, &token, j)
			&& (check_cmd(l_n_m, &token, j)))
		{
			if (check_builtins(token.lower))
				choose_builtin(l_n_m, &token, i);
			else
			{
				l_n_m->pids[i] = fork();
				if (l_n_m->pids[i] < 0)
					free_token_n_structure_exit(&token, l_n_m);
				if (!l_n_m->pids[i])
					child_process(l_n_m, token, i);
			}
		}
		next_iteration(l_n_m, &token, &j, &i);
	}
}

void	kernel_start(t_line_n_mask *l_n_m, size_t start)
{
	size_t	i;

	i = 0;
	kernel(l_n_m, start);
	while (i < l_n_m->cnt_pipes + 1)
	{
		close(l_n_m->pipes[i][0]);
		close(l_n_m->pipes[i][1]);
		i++;
	}
	wait_childs(l_n_m);
}
