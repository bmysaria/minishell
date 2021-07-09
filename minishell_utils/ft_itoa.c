#include "minishell_utils.h"

static	int	ft_abs(int n)
{
	if (n < 0)
		return (n * (-1));
	else
		return (n);
}

static	int	nlen(int n, int fl)
{
	int	size;

	size = 0;
	if (fl)
		size++;
	if (n == 0)
		return (1);
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	int		fl;

	if (n < 0)
		fl = 1;
	else
		fl = 0;
	size = nlen(n, fl);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (0);
	ptr[size--] = '\0';
	if (n == 0)
		ptr[0] = '0';
	while (n)
	{
		ptr[size--] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (fl)
		ptr[0] = '-';
	return (ptr);
}
