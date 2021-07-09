#include "builtins.h"

void	echo_output(char **str, int opt, char *spaces)
{
	int		i;
	int		last;

	last = count_vars(str) - 1;
	i = opt + 1;
	while (str[i])
	{
		if (spaces[i] == 'b')
		{
			ft_putstr_fd(str[i], 1);
			if (i != last)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
}

int	count_spaces(char **str, int opt, char *spaces)
{
	int	ok;
	int	i;

	i = opt + 1;
	ok = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], "-n") && ok == 1 )
			spaces[i] = 'b';
		else if (ft_strcmp(str[i], "-n"))
		{
			ok = 1;
			spaces[i] = 'b';
		}
		i++;
	}
	echo_output(str, opt, spaces);
	return (0);
}

int	ft_echo(char **str)
{
	int		i;
	int		opt;
	char	spaces[100];

	ft_memset(spaces, 'a', 100);
	i = 1;
	opt = 0;
	if (str[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	else if (!ft_strcmp(str[1], "-n"))
	{
		opt = 1;
		i++;
	}
	if (opt == 1 && str[2] == NULL)
		return (0);
	count_spaces(str, opt, spaces);
	if (opt == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
