#include "termcap.h"

char	*realloc_backspace(char *line, t_gnl *gnl)
{
	size_t	i;
	char	*new;
	char	*ptr;

	ptr = line;
	i = ft_strlen(line);
	if (i > 1)
	{
		new = ft_calloc(i - 1, 1);
		if (!(new))
			free_gnl_error(gnl);
		new = ft_memcpy(new, line, i - 2);
		free(ptr);
	}
	else
	{
		free(gnl->edit);
		new = ft_calloc(1, 1);
		if (!new)
			free_gnl_error(gnl);
	}
	return (new);
}

int	backspace(t_gnl *gnl)
{
	tputs(tgetstr("rc", 0), 1, ft_putint);
	tputs(tgetstr("ce", 0), 1, ft_putint);
	gnl->edit = realloc_backspace(gnl->edit, gnl);
	ft_putstr(gnl->edit);
	return (0);
}

int	up(t_gnl *gnl)
{
	char	*ptr;

	if (gnl->flag == 2)
		gnl->history = gnl->history->prev;
	if (gnl->history)
	{
		gnl->flag = 1;
		tputs(tgetstr("rc", 0), 1, ft_putint);
		tputs(tgetstr("ce", 0), 1, ft_putint);
		ptr = gnl->edit;
		gnl->edit = ft_strdup(gnl->history->line);
		free(ptr);
		ft_putstr(gnl->edit);
		if (gnl->history->prev)
			gnl->history = gnl->history->prev;
		else
			gnl->flag = 0;
	}
	return (0);
}

void	new_edit_line(t_gnl *gnl)
{
	char	*new;
	char	*ptr;

	ptr = gnl->edit;
	new = ft_calloc(1, 1);
	if (!new)
		free_gnl_error(gnl);
	gnl->edit = new;
	free(ptr);
	tputs(tgetstr("rc", 0), 1, ft_putint);
	tputs(tgetstr("ce", 0), 1, ft_putint);
	gnl->flag = 0;
}

int	down(t_gnl *gnl)
{
	char	*ptr;

	if (gnl->flag == 1)
		gnl->history = gnl->history->next;
	if (gnl->history)
	{
		if (gnl->history->next)
		{
			gnl->flag = 2;
			tputs(tgetstr("rc", 0), 1, ft_putint);
			tputs(tgetstr("ce", 0), 1, ft_putint);
			gnl->history = gnl->history->next;
			ptr = gnl->edit;
			gnl->edit = ft_strdup(gnl->history->line);
			free(ptr);
			ft_putstr(gnl->edit);
		}
		else
			new_edit_line(gnl);
	}
	return (0);
}
