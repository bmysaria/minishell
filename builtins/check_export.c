#include "builtins.h"

int	export_error(char *line)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("':", 2);
	ft_putstr_fd(" not a valid identifier\n", 2);
	return (-1);
}

int	check_line(char *line, char *eqsign)
{
	char	*start;

	start = line;
	if (*line == '=')
		return (export_error(eqsign));
	else if (*(eqsign - 1) == ' ')
		return (export_error(eqsign));
	else if (!(*start == '_' || ft_isalpha(*start)))
		return (export_error(line));
	if (*(start + 1) != '\0')
		start++;
	while (*start != '=' && *start != '\0')
	{
		if (!(*start == '_' || ft_isalnum(*start)))
			return (export_error(line));
		start++;
	}
	return (0);
}

int	export_validation(char **vars)
{
	int		i;
	char	*equalsign;

	i = 1;
	while (vars[i])
	{
		equalsign = ft_strchr(vars[i], '=');
		if (equalsign)
		{
			if (check_line(vars[i], equalsign) != 0)
				return (-1);
		}
		i++;
	}
	return (0);
}
