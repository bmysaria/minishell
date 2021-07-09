#include "tokenizer.h"

size_t 	get_cnt_after_equal(char *line)
{
	size_t	cnt;
	size_t	i;

	i = 0;
	cnt = 0;
	while (line[i++] != '=')
		;
	while (line[i++])
		cnt++;
	return (cnt);
}

static size_t	get_cnt_env(t_line_n_mask *l_n_m, size_t *start, size_t j)
{
	size_t	cnt;
	char	*env;
	size_t	i;

	cnt = j - *start;
	i = 0;
	env = (char *)malloc(sizeof(char) * cnt + 1);
	if (!env)
		free_and_exit_tokenizer(l_n_m);
	while (*start < j)
		env[i++] = l_n_m->line[(*start)++];
	env[i] = '\0';
	j = 0;
	while ((*(l_n_m->env))[j])
	{
		if (!(ft_strncmp_env(env, (*(l_n_m->env))[j],
				ft_strlen((*(l_n_m->env))[j]))))
		{
			free(env);
			return (get_cnt_after_equal((*(l_n_m->env))[j]));
		}
		j++;
	}
	free(env);
	return (0);
}

static size_t	get_cnt_status(t_line_n_mask *l_n_m)
{
	char	*line;
	size_t	cnt;

	line = ft_itoa(l_n_m->status);
	if (!line)
		free_and_exit_tokenizer(l_n_m);
	cnt = ft_strlen(line);
	free(line);
	return (cnt);
}

size_t	get_cnt_dollar(t_line_n_mask *l_n_m, size_t *start)
{
	size_t	j;

	(*start)++;
	j = *start;
	if (is_digit(l_n_m->line[j]))
	{
		if (l_n_m->line[j])
			(*start)++;
		return (0);
	}
	if (!l_n_m->mask[j] || (!ft_isalpha(l_n_m->line[j])
			&& l_n_m->line[j] != '_' && l_n_m->line[j] != '?'))
	{
		if (l_n_m->mask[j])
			(*start)++;
		return (1);
	}
	if (l_n_m->line[j] == '?')
		return (get_cnt_status(l_n_m));
	while (l_n_m->line[j]
		&& (ft_isalpha(l_n_m->line[j]) || l_n_m->line[j] == '_'
			|| is_digit(l_n_m->line[j])))
		j++;
	return (get_cnt_env(l_n_m, start, j));
}
