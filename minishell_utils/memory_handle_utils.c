#include "minishell_utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dst;
	if (!src && !dst)
		return (dst);
	while (i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	return (str2);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n-- > 0)
		str[n] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = (void *)malloc(count * size);
	if (!str)
		return (0);
	else
	{
		ft_bzero(str, count * size);
		return (str);
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	sim;

	i = 0;
	str = (unsigned char *)b;
	sim = (unsigned char)c;
	while (i < len)
	{
		str[i] = sim;
		i++;
	}
	return (str);
}
