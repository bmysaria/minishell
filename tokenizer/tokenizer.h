#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <dirent.h>
# include "../minishell_utils/minishell_utils.h"
# include "../parser/parser.h"
# include "../termcap/termcap.h"
# include <fcntl.h>

# define IS_DIR ": is a directory\n"
# define CMD_NF ": command not found\n"

typedef struct s_line_n_mask
{
	char		*line;
	char		***env;
	char		*mask;
	int			status;
	char		**free_line;
	int			**pipes;
	int			*pids;
	size_t		cnt_pipes;
	t_gnl		*gnl;
}				t_line_n_mask;

typedef struct s_token
{
	char	**args;
	char	*lower;
	char	*line;
	int		fd_from;
	int		fd_to;
}				t_token;

size_t	condition_handle_dollar(t_line_n_mask *l_n_m, size_t j);
size_t	condition_get_redir_util(t_line_n_mask *l_n_m, size_t start);
size_t	condition_cmd(t_line_n_mask *l_n_m, size_t i);
size_t	is_dir(t_line_n_mask *l_n_m, char *line, char **path);
void	free_path(char **path);
char	*get_redir(t_line_n_mask *l_n_m, size_t start, char **line, size_t j);
size_t	check_builtins(char *line);
size_t	check_cmd(t_line_n_mask *l_n_m, t_token *token, size_t i);
void	free_token_n_structure_exit(t_token *token, t_line_n_mask *l_n_m);
void	free_and_exit_tokenizer(t_line_n_mask *l_n_m);
size_t	handle_redirects(t_line_n_mask *l_n_m, t_token *token, size_t i);
size_t	get_cnt_dollar(t_line_n_mask *l_n_m, size_t *start);
size_t	get_cnt_after_equal(char *line);
void	handle_string_dollar(t_line_n_mask *l_n_m, char *line,
			size_t *start, size_t *i);
size_t	condition_redirects_1(t_line_n_mask *l_n_m, size_t i, char c);
size_t	condition_redirects_2(t_line_n_mask *l_n_m, size_t i, char c);
size_t	condition_redirects3(t_line_n_mask *l_n_m, size_t start);
size_t	redirect_error(t_token *token, t_line_n_mask *l_n_m);
void	handle_cmd(t_line_n_mask *l_n_m, t_token *token, size_t i);
size_t	condition_cmd_limits(t_line_n_mask *l_n_m, size_t i);
size_t	handle_cmd_condition(t_line_n_mask *l_n_m, size_t i);
void	free_and_exit_tokenizer_cmd(t_token *token, t_line_n_mask *l_n_m,
			size_t i);
void	body_condition_dollar(t_line_n_mask *l_n_m, char *line, size_t *start,
			size_t *i);
void	body_condition_digit(t_line_n_mask *l_n_m, size_t *start);

#endif