#include "tokenizer.h"

static size_t	check_slash(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
		if (line[i++] == '/')
			return (1);
	return (0);
}

size_t	is_dir(t_line_n_mask *l_n_m, char *line, char **path)
{
	DIR		*dir;

	free_path(path);
	dir = opendir(line);
	if (check_slash(line) && dir)
	{
		write(2, line, ft_strlen(line));
		write(2, IS_DIR, ft_strlen(IS_DIR));
		l_n_m->status = 126;
		closedir(dir);
		return (0);
	}
	else if (!check_slash(line))
	{
		write(2, line, ft_strlen(line));
		write(2, CMD_NF, ft_strlen(CMD_NF));
		l_n_m->status = 127;
		if (dir)
			closedir(dir);
		return (0);
	}
	return (1);
}
