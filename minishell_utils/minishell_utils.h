#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <termcap.h>

void		to_lower(char *line);
int			ft_strncmp_cmd(const char *s1, const char *s2, size_t n);
int			ft_strncmp_env(const char *s1, const char *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
int			ft_putint(int c);
int			ft_isalpha(int c);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
char		**ft_split(char *s, char c);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
int			is_digit(char c);
int			ft_is_printable(int c);
char		*ft_strrchr(const char *s, int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
long long	ft_atoi(const char *str);
int			all_digits(char *line);
void		ft_putstr(char *str);

#endif