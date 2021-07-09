#include "builtins.h"

void	exit_error(int error, char *arg)
{
	if (error == 1)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (error == 2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

long long	exit_with_atoi(t_token *token)
{
	long long	a;

	a = ft_atoi(token->args[1]);
	if ((token->args[1][0] == '-' && a > 0) || (token->args[1][0] !=
												'-' && a < 0))
	{
		exit_error(2, token->args[1]);
		a = 255;
	}
	else
	{
		if (a < 0)
			a = a - 256;
		ft_putstr_fd("exit\n", 1);
	}
	return (a);
}

int	ft_norm_exit(t_line_n_mask *l_n_m, t_token *token)
{
	long long	a;

	a = 0;
	if (!(token->args[1]))
		ft_putstr_fd("exit\n", 1);
	else if (token->args[1] && !token->args[2])
	{
		if (all_digits(token->args[1]) == -1)
		{
			a = 255;
			exit_error(2, token->args[1]);
		}
		else
			a = exit_with_atoi(token);
	}
	free_token_n_structure_exit_2(token, l_n_m);
	exit (a);
}

int	ft_exit(t_line_n_mask *l_n_m, t_token *token)
{
	int	count;

	count = count_vars(token->args);
	if (count < 3)
		ft_norm_exit(l_n_m, token);
	exit_error(1, NULL);
	return (1);
}
