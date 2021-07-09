#include "tokenizer.h"

char	*get_path(t_line_n_mask *l_n_m, t_token *token)
{
	char	*after_equal;
	char	*ptr_path;
	size_t	j;
	size_t	i;

	j = -1;
	i = 0;
	while ((*(l_n_m->env))[j + 1])
		if (!ft_strncmp_env("PATH", (*(l_n_m->env))[++j], 4))
			break ;
	if (!(*(l_n_m->env))[j])
		return (0);
	ptr_path = (*(l_n_m->env))[j];
	after_equal = (char *)malloc(get_cnt_after_equal(ptr_path) + 1);
	if (!after_equal)
		free_token_n_structure_exit(token, l_n_m);
	j = 0;
	while (ptr_path[j++] != '=')
		;
	while (i < get_cnt_after_equal(ptr_path))
		after_equal[i++] = ptr_path[j++];
	after_equal[i] = '\0';
	return (after_equal);
}

static size_t	change_cmd(char **path, size_t i, t_token *token,
t_line_n_mask *l_n_m)
{
	char	*temp_ptr;
	char	*new_path;

	new_path = ft_strjoin(path[i], "/");
	if (!new_path)
	{
		free_path(path);
		free_token_n_structure_exit(token, l_n_m);
	}
	temp_ptr = new_path;
	new_path = ft_strjoin(new_path, token->lower);
	if (!new_path)
	{
		free(temp_ptr);
		free_path(path);
		free_token_n_structure_exit(token, l_n_m);
	}
	free_path(path);
	free(temp_ptr);
	free(token->args[0]);
	token->args[0] = new_path;
	return (1);
}

size_t	check_builtins(char *line)
{
	if (line)
	{
		if (!ft_strncmp_cmd("cd", line, ft_strlen(line)))
			return (1);
		if (!ft_strncmp_cmd("pwd", line, ft_strlen(line)))
			return (1);
		if (!ft_strncmp_cmd("echo", line, ft_strlen(line)))
			return (1);
		if (!ft_strncmp_cmd("export", line, ft_strlen(line)))
			return (1);
		if (!ft_strncmp_cmd("unset", line, ft_strlen(line)))
			return (1);
		if (!ft_strncmp_cmd("env", line, ft_strlen(line)))
			return (1);
		if (!ft_strncmp_cmd("exit", line, ft_strlen(line)))
			return (1);
	}
	return (0);
}

static size_t	find_cmd(t_line_n_mask *l_n_m, t_token *token, char **path,
struct dirent *entry)
{
	DIR				*dir;
	size_t			j;

	j = 0;
	while (path[j])
	{
		dir = opendir(path[j]);
		if (dir)
		{
			entry = readdir(dir);
			while (entry != 0)
			{
				if (!(ft_strncmp_cmd(token->lower, entry->d_name,
							ft_strlen(entry->d_name))))
				{
					closedir(dir);
					return (change_cmd(path, j, token, l_n_m));
				}
				entry = readdir(dir);
			}
			closedir(dir);
		}
		j++;
	}
	return (is_dir(l_n_m, token->args[0], path));
}

size_t	check_cmd(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	char			**path;
	struct dirent	*entry;
	char			*get_pth;

	entry = 0;
	handle_cmd(l_n_m, token, i);
	if (token->args[0])
	{
		token->lower = ft_strdup(token->args[0]);
		if (!token->lower)
			free_token_n_structure_exit(token, l_n_m);
		to_lower(token->lower);
	}
	if (check_builtins(token->lower))
		return (1);
	get_pth = get_path(l_n_m, token);
	if (!get_pth)
		return (is_dir(l_n_m, token->args[0], 0));
	path = ft_split(get_pth, ':');
	if (!path)
		free_token_n_structure_exit(token, l_n_m);
	if (token->args[0])
		return (find_cmd(l_n_m, token, path, entry));
	return (0);
}
