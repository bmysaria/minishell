#include "builtins.h"

void	free_export(t_line_n_mask *l_n_m, t_token *token, char **vars, int i)
{
	if (vars)
		free_vars(vars, i);
	free_token_n_structure_exit(token, l_n_m);
}

char	**export_one_var(char *var, char **envp, t_line_n_mask *l_n_m,
					  t_token *token)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc((sizeof(char *) * (count_vars(envp) + 2)));
	if (!res)
		free_export(l_n_m, token, NULL, 0);
	while (*envp)
	{
		res[i] = ft_strdup(*envp);
		if (!res[i])
			free_export(l_n_m, token, res, i - 1);
		envp++;
		i++;
	}
	res[i] = ft_strdup(var);
	if (!res[i])
		free_export(l_n_m, token, res, i - 1);
	res[i + 1] = NULL;
	return (res);
}

int	ft_export(t_line_n_mask *l_n_m, t_token *token)
{
	int		validation;

	if (!token->args[1])
	{
		sort_vars(*l_n_m->env);
		return (0);
	}
	validation = export_validation(token->args);
	if (validation == 0)
	{
		manage_duplication(token->args, *l_n_m->env, l_n_m, token);
		return (0);
	}
	return (1);
}
