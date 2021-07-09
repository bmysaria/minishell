#include "builtins.h"

void	print_arg(char **envp, int i, int j)
{
	{
		ft_putstr_fd("=\"", 1);
		j++;
		while (envp[i][j] != '\0')
		{
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		ft_putstr_fd("\"", 1);
	}
}

void	print_envp(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (envp[i][j] != '=' && envp[i][j] != '\0')
		{
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		if (envp[i][j] == '=' && envp[i][j + 1] != '\0')
			print_arg(envp, i, j);
		ft_putstr_fd("\n", 1);
		j = 0;
		i++;
	}
}

void	ft_swap(char **v1, char **v2)
{
	char	*tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void	sort_vars(char **v)
{
	int		i;
	int		j;
	int		count;

	j = 0;
	count = count_vars(v) + 1;
	while (count > 0)
	{
		i = 0;
		while (v[i] && v[i + 1] && i <= count)
		{
			while (v[i][j] == v[i + 1][j] && v[i][j + 1] != '=' && v[i][j +
				1] != '\0' && v[i + 1][j + 1] != '=' && v[i + 1][j + 1] != '\0')
				j++;
			if (v[i][j] - v[i + 1][j] > 0)
				ft_swap(&(v[i]), &(v[i + 1]));
			j = 0;
			i++;
		}
		count--;
	}
	print_envp(v);
}
