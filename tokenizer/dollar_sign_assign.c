#include "tokenizer.h"

static char	*get_env_rvalue(char *line, t_line_n_mask *l_n_m)
{
	size_t	i;
	size_t	j;
	char	*env_rvalue;
	size_t	cnt;

	i = 0;
	j = 0;
	cnt = get_cnt_after_equal(line);
	env_rvalue = (char *)malloc(sizeof(char) * cnt + 1);
	if (!env_rvalue)
		free_and_exit_tokenizer(l_n_m);
	while (line[i++] != '=')
		;
	while (line[i])
		env_rvalue[j++] = line[i++];
	env_rvalue[j] = '\0';
	return (env_rvalue);
}

static char	*get_env_string(t_line_n_mask *l_n_m, size_t *start, size_t j,
size_t i)
{
	char	*env_lvalue;

	env_lvalue = (char *)malloc(sizeof(char) * (j - *start) + 1);
	if (!env_lvalue)
		free_and_exit_tokenizer(l_n_m);
	while (*start < j)
		env_lvalue[i++] = l_n_m->line[(*start)++];
	env_lvalue[i] = '\0';
	j = 0;
	while ((*(l_n_m->env))[j])
	{
		if (!(ft_strncmp_env(env_lvalue, (*(l_n_m->env))[j],
				ft_strlen((*(l_n_m->env))[j]))))
		{
			free(env_lvalue);
			return (get_env_rvalue((*(l_n_m->env))[j], l_n_m));
		}
		j++;
	}
	free(env_lvalue);
	env_lvalue = ft_strdup("");
	if (!env_lvalue)
		free_and_exit_tokenizer(l_n_m);
	return (env_lvalue);
}

static void	append_line(char *line, char *env, size_t *i)
{
	size_t	j;

	j = 0;
	while (env[j])
		line[(*i)++] = env[j++];
	free(env);
}

static void	handle_string_question(t_line_n_mask *l_n_m, char *line, size_t *i)
{
	char	*str;
	size_t	len;
	size_t	j;

	str = ft_itoa(l_n_m->status);
	if (!str)
		free_and_exit_tokenizer(l_n_m);
	j = 0;
	len = ft_strlen(str);
	while (j < len)
		line[(*i)++] = str[j++];
	free(str);
}

void	handle_string_dollar(t_line_n_mask *l_n_m, char *line,
size_t *start, size_t *i)
{
	size_t	j;
	size_t	cur;
	char	*env;

	cur = 0;
	(*start)++;
	j = *start;
	if (is_digit(l_n_m->line[j]))
		return (body_condition_digit(l_n_m, start));
	if (condition_handle_dollar(l_n_m, j))
		return (body_condition_dollar(l_n_m, line, start, i));
	if (l_n_m->line[j] == '?')
	{
		handle_string_question(l_n_m, line, i);
		(*start)++;
		return ;
	}
	while (l_n_m->line[j]
		&& (ft_isalpha(l_n_m->line[j]) || l_n_m->line[j] == '_'
			|| is_digit(l_n_m->line[j])))
		j++;
	env = get_env_string(l_n_m, start, j, cur);
	append_line(line, env, i);
}
