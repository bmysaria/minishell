#include "tokenizer.h"

static size_t	check_dir_error(t_token *token, t_line_n_mask *l_n_m,
char *is_a_directory, DIR *dir)
{
	closedir(dir);
	l_n_m->status = 1;
	write(2, token->line, ft_strlen(token->line));
	write(2, is_a_directory, ft_strlen(is_a_directory));
	free(token->line);
	token->line = 0;
	return (0);
}

static size_t	check_fd_error(t_token *token, t_line_n_mask *l_n_m,
char *not_file_error)
{
	if (token->fd_from < 0)
		token->fd_from = 0;
	if (token->fd_to < 0)
		token->fd_to = 0;
	l_n_m->status = 1;
	write(2, token->line, ft_strlen(token->line));
	write(2, not_file_error, ft_strlen(not_file_error));
	free(token->line);
	token->line = 0;
	return (0);
}

size_t 	redirect_error(t_token *token, t_line_n_mask *l_n_m)
{
	DIR		*dir;
	char	*not_file_error;
	char	*is_a_directory;

	is_a_directory = ": is a directory\n";
	not_file_error = ": No such file or directory\n";
	if (token->line)
	{
		dir = opendir(token->line);
		if (dir)
			return (check_dir_error(token, l_n_m, is_a_directory, dir));
	}
	if (token->line && (token->fd_from < 0 || token->fd_to < 0))
		return (check_fd_error(token, l_n_m, not_file_error));
	return (1);
}
