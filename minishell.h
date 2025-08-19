/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:05:23 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 21:10:43 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <limits.h>
# define SINGLE 20
# define DOUBLE 10
# define ALLOC 1
# define CLEAR_DATA 2

typedef struct s_memory
{
	void			*address;
	struct s_memory	*next;

}					t_memory;

typedef enum e_tokentype
{
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	APPEND,
	HERDOC,
	DOUBLE_Q,
	SINGLE_Q,
	DELEMTER,
	EXPAN,
	RED_FILE,
}					t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*previous;
	int				fd_reder;
	int				heredoc_expn;
	int				ambg;
	int				removed;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	char			*cmd;
	char			**cmd_args;
	struct s_exec	*next;
	int				flag;
}					t_exec;

typedef struct s_shell
{
	char			*input;
	char			*expn;
	t_token			*lst;
	t_exec			*exec;
	t_env			*envp;
}					t_shell;

typedef struct s_expand
{
	bool			single_q;
	bool			double_q;
	int				index;
	int				start_index;
	char			*c;
}					t_expand;

typedef struct s_expand_ctx
{
	char			*new_value;
	bool			reset_flag;
	t_expand		expand_state;
	t_env			*envp;
	char			*source_string;
}					t_expand_ctx;

typedef struct s_heredoc_ctx
{
	char			*tmp_file;
	int				fd_out;
	int				fd_in;
	int				status;
}					t_heredoc_ctx;

typedef struct s_split_cmd
{
	char			*cmd;
	t_tokentype		type;
}					t_split_cmd;

typedef enum s_vartype
{
	WORD_V,
	VAR,
}					t_vartype;

typedef struct s_var
{
	char			*value;
	struct s_var	*next;
	t_vartype		type;
}					t_var;

typedef struct s_proc_ctx
{
	t_split_cmd		*s;
	t_expand_ctx	*ctx;
}	t_proc_ctx;

void				skip_till_pipe(t_token **lst);
void				skip_s(char *str, int *index);
char				*remove_q(char *val);
int					pip_check(char *str, int *i);
void				init_expan(t_expand_ctx *ctx, char *str, t_env *envp);
int					skip_spaces(char *s, int i);
void				ft_split_expanded(char *val, t_token **lst, t_env *env);
char				**a_split(char *s);
int					check_space(char *str);
char				*get_env(char *val, t_env *envp);
int					ft_quotes_type(char *str);
int					ft_check_quots(char *cmd);
size_t				ft_strlen(char *str);
int					ft_parse_command(char *string);
char				*strj(char *s1, char *s2);
void				ft_syntax_error(void);
char				*subs(char *s, unsigned int start, size_t len);
t_token				*s_cmd(char **command, t_env *envp);
char				*ft_strchr(char *s, int c);
void				ft_lstnew(t_token **lst, t_split_cmd s, t_env *e, int r);
t_token				*ft_lstlast(t_token *lst);
void				ft_lstadd_back(t_token **lst, t_token *new);
int					ft_is_space(char c);
char				**ft_split(char *s);
int					ft_is_space(char c);
bool				ft_pip_check(char *str);
bool				ft_redirect_in(char *str);
bool				ft_redirect_out(char *str);
bool				ft_append(char *str);
t_tokentype			ft_token_type(t_token *lst, char *str);
int					ft_var_check(char *str);
char				*ft_strdup(char *src);
bool				ft_heredoc(char *str);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t				ft_strlcat(char *s1, char *s2, size_t n);
int					variable_skip(char *val, int index);
int					ft_expand(t_token *lst, t_env *envp);
int					ft_heredoc_handle(t_token *lst, t_env *env, int fd_out);
char				*exp_val(char *value, t_env *envp);
int					ft_check_braces(char *str);
int					ft_stop_redirect(t_token *lst);
void				handler(int sig);
int					delimter(char *s, size_t index);
void				ambigous_red(void);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					check_id(char *var);
int					recevied_from_input(int set, int st);
int					check_redirection_pipe(char *str, int *index);
void				default_signal(void);
void				child_signal(char *cmd);
size_t				skip_tillvar(char *val, size_t i);
int					check_exp_type(t_tokentype type);
int					dollar_case(char *string);
int					check_env(char *value, t_env *e);
int					ft_operator_count(char *str, int index, char c);
t_var				*s_var(char *s);
void				heredoc_signal(int sig);
int					handle_redirects(t_token **lst, t_exec *node);

void				*ft_malloc(size_t size, int flag);

char				**convert_t_env(t_env *env);
int					is_builtin(char *cmd);
void				execute_builtin(t_exec *exec, t_env **env, bool forked);

void				getcwd_fail(char *path, t_env **env, char **hold_pwd,
						char *newpwd);
void				update_oldpwd(t_env **env, char *oldpwd);
int					change_dir(char *path, t_env **env, char **hold_pwd);
char				*ft_cd(char **opt, t_env **env);

int					is_valid_option(char *str);
int					ft_echo(char **cmd, int fd);

void				init_default_env(t_env **env, char *pwd);
t_env				*init_env(char **envp);
char				*get_env_value(t_env **env, char *path);
t_env				*find_env(t_env *env, char *key);
int					ft_env(t_env *env, int fd);

int					check_exit_status(pid_t last_pid);
void				cmd_not_found(char *cmd);
int					parent_thing(int *fd, t_exec *head);
void				setup_child(int *fd, t_env *path, t_exec *head, int bltn);

int					ft_lstsize_env(t_env *env);
t_exec				*new_node(void);
void				ft_lstadd_back_exec(t_env **lst, t_env *new);
int					ignore_first_cmd(int res, int get);

void				call_execve(t_exec *head, t_env *env);
void				in_child(t_exec *head, t_env **env, int *fd);
pid_t				execute_cmd(t_exec *head, t_env **env);
int					execution(t_exec *exec, t_env **env);

t_env				*ft_lstlast_exec(t_env *lst);
int					ft_lstsize(t_exec *exec);
void				add_back(t_exec **head, t_exec *new);
t_env				*ft_lstnew_exec(char *key, char *value);

void				ft_putstr_fd(char *s, int fd);
int					ft_strncmp(char *s1, char *s2, size_t n);
char				*ft_strstr(char *str, char *to_find);
char				*ft_strdup2(char *src);
int					is_empty(char *s);

void				ambigous_red(void);
int					e_status(int sts, int set);
int					is_valid_exit(char *opt);
void				err_num(char *opt);
int					ft_exec_exit(char **opt, bool forked);

int					is_valid_export(char *opt);
void				swap_env(t_env *a, t_env *b);
void				bubble_sort_env(t_env *env);
void				print_sorted_env(t_env *env, int fd);

void				handle_plus_equal(char *opt, t_env **env);
void				handle_equal_or_none(char *opt, t_env **env);
void				err_identifier(char *opt);
int					ft_export(char **opt, t_env **env, int fd);

char				*search_cmd_in_path(char **arr, char *cmd);
char				*get_cmd_path(char *cmd, char *path);

char				*ft_itoa(int n);
int					ft_atoi(const char *str, int *flag);

char				**ft_split_exec(char const *s, char c);

int					init_heredoc_ctx(t_heredoc_ctx *ctx, t_token **lst);
int					handle_heredoc(t_token *lst, t_env *env);
int					handle_redirect_in(t_token **lst, t_exec *node);
int					handle_append(t_token **lst, t_exec *node);
int					handle_redirect_out(t_token **lst, t_exec *node);

int					count_until_pipe(t_token *lst);
void				handle_word(t_token *lst, t_exec *node, int *i);
int					handle_redirects(t_token **lst, t_exec *node);
int					fill_node(t_token **lst, t_exec *node);
t_exec				*convert_token_to_exec(t_token *lst);

int					pwd_and_oldpwd(t_env *env, int fd);
int					ft_pwd(t_env *env, int fd);

void				delet_node(t_env **env, char *key);
void				ft_unset(char **opt, t_env **env);

int					ft_strcmp(char *s1, char *s2);
void				handler(int sig);
char				*ft_remove_quotes(t_expand_ctx *ctx, char *tmp);
int					delimter(char *s, size_t index);
bool				handle_quotes(char *str, t_expand *exp);
int					check_imbguous(t_token **lst, t_exec *node);

#endif
