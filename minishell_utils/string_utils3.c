#include "minishell_utils.h"

static int	ft_tolower(int c)
{
	if (('A' <= c) && (c <= 'Z'))
		return (c + 32);
	return (c);
}

void	to_lower(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		line[i] = ft_tolower(line[i]);
		i++;
	}
}

int	is_digit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

int	ft_is_printable(int c)
{
	if (!(c >= 32 && c <= 127))
		return (0);
	return (1);
}
