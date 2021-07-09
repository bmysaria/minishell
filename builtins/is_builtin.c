#include "builtins.h"
#include "../executing/executing.h"

static void	assign_fd(int *fdin, int *fdout, t_line_n_mask *l_n_m)
{
	*fdin = dup(0);
	if (*fdin < 0)
		return (dup_error(l_n_m));
	*fdout = dup(1);
	if (*fdout < 0)
		return (dup_error(l_n_m));
}

void	choose_builtin(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	int	fdin;
	int	fdout;

	assign_fd(&fdin, &fdout, l_n_m);
	change_io(l_n_m, token, i, 0);
	if (!(ft_strcmp(token->lower, "echo")))
		l_n_m->status = ft_echo(token->args);
	else if (!(ft_strcmp(token->lower, "cd")))
		l_n_m->status = ft_cd(token, l_n_m);
	else if (!(ft_strcmp(token->lower, "pwd")))
		l_n_m->status = ft_pwd();
	else if (!(ft_strcmp(token->lower, "env")))
		l_n_m->status = ft_env(*l_n_m->env);
	else if (!(ft_strcmp(token->lower, "export")))
		l_n_m->status = ft_export(l_n_m, token);
	else if (!(ft_strcmp(token->lower, "unset")))
		l_n_m->status = ft_unset(l_n_m, token);
	else if (!(ft_strcmp(token->lower, "exit")))
		l_n_m->status = ft_exit(l_n_m, token);
	if (dup2(fdin, 0) < 0)
		return (dup_error(l_n_m));
	if (dup2(fdout, 1) < 0)
		return (dup_error(l_n_m));
}

void	free_and_exit_tokenizer_2(t_line_n_mask *l_n_m)
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
}

void	free_token_n_structure_exit_2(t_token *token, t_line_n_mask *l_n_m)
{
	size_t	j;

	j = 0;
	while (token->args[j])
		free(token->args[j++]);
	free(token->args);
	free(token->lower);
	free_and_exit_tokenizer_2(l_n_m);
}
