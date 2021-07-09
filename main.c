#include "minishell.h"
#include "builtins/builtins.h"

void	parse_n_execute(t_gnl *gnl, char ***env)
{
	size_t	i;
	char	*mask;

	i = 0;
	mask = ft_calloc(ft_strlen(gnl->history->line) + 1, sizeof(char));
	if (!mask)
	{
		free_gnl(gnl);
		exit (1);
	}
	while (i < ft_strlen(gnl->history->line))
		mask[i++] = '1';
	if (!get_mask_normal(gnl->history->line, mask))
		return ;
	if (!parser(gnl->history->line, mask))
	{
		free(mask);
		gnl->status = 258;
		return ;
	}
	handle_semicolons(gnl, mask, env);
	free(mask);
}

int	comparison(t_gnl *gnl)
{
	if (!ft_strcmp(gnl->str, "\e[D") || !ft_strcmp(gnl->str, "\t") || !ft_strcmp
		(gnl->str, "\e[C"))
		ft_memset(gnl->str, 0, 10);
	if (!ft_strcmp(gnl->str, "\n"))
		return (enter(gnl));
	if (!ft_strcmp(gnl->str, "\e[A"))
		up(gnl);
	else if (!ft_strcmp(gnl->str, "\e[B"))
		down(gnl);
	else if (ft_strcmp(gnl->str, "\n") && ft_strcmp(gnl->str, "\4"))
		get_command(gnl);
	if (!ft_strcmp(gnl->str, "\177"))
		backspace(gnl);
	if (!ft_strcmp(gnl->str, "\4"))
	{
		ft_memset(gnl->str, 0, 10);
		if (ft_strlen(gnl->edit) == 0)
		{
			free_gnl(gnl);
			ft_putstr_fd("\nexit\n", 1);
			set_terminal(gnl, 0);
			exit (0);
		}
	}
	return (0);
}

int	input(t_gnl *gnl)
{
	while (1)
	{
		signal(SIGINT, sig_c);
		set_terminal(gnl, 1);
		ft_memset(gnl->str, 0, 10);
		gnl->l = read(0, gnl->str, 10);
		if (comparison(gnl) == 1)
		{
			signal(SIGINT, sig_c_2);
			set_terminal(gnl, 0);
			if (g_var == 1 && gnl->status != 130)
			{
				gnl->status = g_var;
				g_var = 0;
			}
			else if (g_var == 1 && gnl->status)
				g_var = 0;
			parse_n_execute(gnl, gnl->env);
			set_terminal(gnl, 1);
			tputs("minishell=):", 1, ft_putint);
			tputs(save_cursor, 1, ft_putint);
		}
	}
	return (0);
}

void	set_terminal(t_gnl *gnl, int flag)
{
	int	res;

	if (flag == 1)
	{
		gnl->term->c_lflag &= ~(ECHO);
		gnl->term->c_lflag &= ~(ICANON);
		gnl->term->c_cc[VTIME] = 0;
		gnl->term->c_cc[VMIN] = 1;
		res = tcsetattr(0, TCSANOW, gnl->term);
		if (res < 0)
			free_gnl_error(gnl);
		res = tgetent(0, gnl->term_name);
		if (res < 0)
			free_gnl_error(gnl);
	}
	if (flag == 0)
	{
		res = tcsetattr(0, TCSANOW, gnl->reset_term);
		if (res < 0)
			free_gnl_error(gnl);
	}
}

int	main(int argc, char const **argv, char **env)
{
	t_gnl	*gnl;
	char	**envp;
	char	*term;

	(void)(argv);
	(void)(argc);
	term = (char *)getenv("TERM");
	if (!term)
		return (1);
	if (!env[0])
		return (0);
	envp = copy_envp(env);
	if (!envp)
		exit (1);
	gnl = gnl_init();
	if (!gnl)
		free_gnl(gnl);
	gnl->env = &envp;
	signal(SIGQUIT, sig_slash);
	signal(SIGINT, sig_c);
	set_terminal(gnl, 1);
	tputs("minishell=):", 1, ft_putint);
	tputs(save_cursor, 1, ft_putint);
	input(gnl);
	return (0);
}
