#include "builtins.h"

int	check_duplication(char *v, char **envp)
{
	int		flag;
	int		i;
	char	*e;
	char	*ptr;

	i = 0;
	flag = 0;
	while (*envp && flag == 0)
	{
		e = *envp;
		ptr = *envp;
		while (v[i] == e[i] && v[i] != '=' && e[i] != '=')
			i++;
		if (v[i] == '=' && (e[i] == '=' || e[i] == '\0'))
		{
			*envp = ft_strdup(v);
			free(ptr);
			i = 0;
			flag = 1;
		}
		envp++;
	}
	return (flag);
}

void	manage_duplication(char **vars, char **envp, t_line_n_mask *l_n_m,
						  t_token *token)
{
	char	**new_envp;
	int		i;

	i = 1;
	while (vars[i])
	{
		check_duplication(vars[i], envp);
		if (check_duplication(vars[i], envp) == 0)
		{
			new_envp = export_one_var(vars[i], envp, l_n_m, token);
			free_vars(envp, count_vars(envp) - 1 );
			envp = new_envp;
		}
		i++;
	}
	*l_n_m->env = envp;
}
