#include "termcap.h"

int	enter(t_gnl *gnl)
{
	int	res;

	if (gnl->edit[0] != '\0')
	{
		write(1, "\n", 1);
		res = lst_create_add(&gnl->history, ft_strdup(gnl->edit));
		if (res == -1)
			free_gnl_error(gnl);
		free(gnl->edit);
		gnl->edit = ft_calloc(1, 1);
		if (!gnl->edit)
			free_gnl(gnl);
		gnl->flag = 0;
		return (1);
	}
	else
	{
		write(1, "\n", 1);
		tputs("minishell=):", 1, ft_putint);
		tputs(save_cursor, 1, ft_putint);
		if (gnl->history)
			while (gnl->history->next)
				gnl->history = gnl->history->next;
	}
	return (0);
}

int	get_command(t_gnl *gnl)
{
	char	*ptr;

	ptr = gnl->edit;
	write(1, gnl->str, gnl->l);
	if (ft_is_printable(gnl->str[0]))
	{
		gnl->edit = ft_strjoin(gnl->edit, gnl->str);
		free(ptr);
	}
	return (0);
}
