#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../tokenizer/tokenizer.h"

void	choose_builtin(t_line_n_mask *l_n_m, t_token *token, size_t i);
void	free_vars(char **vars, int i);
int		count_vars(char **vars);
char	**copy_envp(char **envp);
char	**export_one_var(char *var, char **envp, t_line_n_mask *l_n_m,
			t_token *token);
char	**check_for_equal_sign(char **vars);
int		export_validation(char **vars);
char	**collect_valid_vars(int count, char **vars, t_line_n_mask *l_n_m,
			t_token *token);
void	manage_duplication(char **vars, char **envp, t_line_n_mask *l_n_m,
			t_token *token);
int		ft_echo(char **str);
int		ft_cd(t_token *token, t_line_n_mask *l_n_m);
int		ft_pwd(void);
int		ft_env(char **envp);
char	*return_new_pwd(void);
int		ft_unset(t_line_n_mask *l_n_m, t_token *token);
char	**unset(char **vars, char **envp, t_line_n_mask *l_n_m, t_token *token);
int		ft_exit(t_line_n_mask *l_n_m, t_token *token);
void	sort_vars(char **v);
void	free_export(t_line_n_mask *l_n_m, t_token *token, char **vars, int i);
int		ft_export(t_line_n_mask *l_n_m, t_token *token);
int		cd_error(char *path);
int		change_directory(char *path);
int		absolute_or_relative_path(char *path, char **args, t_token *token,
			t_line_n_mask *l_n_m);
int		join_oldpwd(t_token *token, t_line_n_mask *l_n_m);
char	*return_env(char *env, char **envp);
void	free_token_n_structure_exit_2(t_token *token, t_line_n_mask *l_n_m);

#endif
