#include "minishell_utils.h"

int	ft_strncmp_cmd(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (1);
	if (!(*s1) || !(*s2))
		return (1);
	while (*s1 && *s2 && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	if (n || *s1 || *s2)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((('a' <= c) && (c <= 'z'))
		|| (('A' <= c) && (c <= 'Z')))
		return (1);
	return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd == -1)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd == -1)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
