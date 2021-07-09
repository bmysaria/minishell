#include "tokenizer.h"

void	free_path(char **path)
{
	size_t	i;

	i = 0;
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
}

void	free_and_exit_tokenizer_cmd(t_token *token, t_line_n_mask *l_n_m,
size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
		free(token->args[j++]);
	free(token->args);
	free_and_exit_tokenizer(l_n_m);
}

void	free_token_n_structure_exit(t_token *token, t_line_n_mask *l_n_m)
{
	size_t	j;

	j = 0;
	while (token->args[j])
		free(token->args[j++]);
	free(token->args);
	free(token->lower);
	free_and_exit_tokenizer(l_n_m);
}

void	free_and_exit_tokenizer(t_line_n_mask *l_n_m)
{
	size_t	j;

	j = 0;
	free_gnl(l_n_m->gnl);
	free (l_n_m->mask);
	if (l_n_m->pids)
		free(l_n_m->pids);
	if (l_n_m->pipes)
	{
		while (j < l_n_m->cnt_pipes + 1)
			free(l_n_m->pipes[j++]);
		free(l_n_m->pipes);
	}
	if (l_n_m->free_line)
		free(*l_n_m->free_line);
	exit (1);
}
