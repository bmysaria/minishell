#include "builtins.h"
#include "errno.h"
#include "string.h"

int	ft_pwd(void)
{
	char	*pwd;
	char	*buff;
	size_t	len;

	buff = NULL;
	pwd = getcwd(buff, 0);
	if (pwd)
	{
		len = ft_strlen(pwd);
		write(1, pwd, len);
		write(1, "\n", 1);
		free(buff);
		free(pwd);
		return (0);
	}
	return (1);
}

char	*return_new_pwd(void)
{
	char	*pwd;
	char	*buff;

	buff = NULL;
	pwd = getcwd(buff, 0);
	free(buff);
	return (pwd);
}

int	cd_error(char *path)
{
	char	*message;

	message = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	change_directory(char *path)
{
	int	res;

	res = chdir(path);
	free(path);
	return (res);
}

int	ft_cd(t_token *token, t_line_n_mask *l_n_m)
{
	int		res;
	char	**args;
	char	*path;

	args = token->args;
	path = ft_calloc(1, 1);
	if (!path)
		free_token_n_structure_exit(token, l_n_m);
	res = absolute_or_relative_path(path, args, token, l_n_m);
	if (res == 0)
	{
		if (return_env("PWD", *l_n_m->env) == NULL)
			return (0);
		else
			return (join_oldpwd(token, l_n_m));
	}
	if (res < 0)
		return (cd_error(path));
	return (1);
}
