#ifndef TERMCAP_H
# define TERMCAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>
# include "../minishell_utils/minishell_utils.h"
# include "errno.h"

typedef struct s_list	t_list;
typedef struct s_gnl	t_gnl;

struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*line;
};

struct s_gnl
{
	char			***env;
	char			*edit;
	t_list			*history;
	int				l;
	char			*str;
	int				flag;
	char			*term_name;
	struct termios	*term;
	struct termios	*reset_term;
	int				status;
};

void	sig_slash(int signum);
void	sig_c(int signum);
void	sig_c_2(int signum);
int		lst_create_add(t_list **lst, char *line);
void	ft_putstr(char *str);
int		up(t_gnl *gnl);
int		down(t_gnl *gnl);
int		enter(t_gnl *gnl);
int		backspace(t_gnl *gnl);
int		input(t_gnl *gnl);
int		get_command(t_gnl *gnl);
t_gnl	*gnl_init(void);
void	free_gnl_error(t_gnl *gnl);
void	free_gnl(t_gnl *gnl);
int		ft_strcmp(const char *s1, const char *s2);
void	set_terminal(t_gnl *gnl, int flag);

#endif