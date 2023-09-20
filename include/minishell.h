/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:27:02 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/28 16:33:06 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MAX_LINE_LEN 4096
# define SGL_QT 39
# define DBL_QT 34
# define RED_I 60
# define RED_O 62
# define PIPE 124

typedef enum token_types
{
	T_RED_I_SGL = '<',
	T_RED_O_SGL = '>',
	T_RED_O_DBL,
	T_RED_I_DBL,
	T_STR,
	T_INPUT,
	T_OUTPUT,
	T_APPEND,
	T_HEREDOC,
	T_CMD,
	T_BEG,
	T_PIPE = '|'
}	t_token_types;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*string;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	char			*cmd;
	pid_t			pid;
	char			**args;
	t_token			*first_token;
	int				fd[2];
	int				fdin;
	int				fdout;	
	int				fdin_init;
	int				fdout_init;
	int				cmd_ok;
	struct s_pipe	*next;
	struct s_pipe	*previous;
}	t_pipe;

typedef struct s_bash
{
	int		err;
	int		echo;
	int		h_f;
	char	**exec;
	char	**envp;
	char	*input;
	char	*f;
	char	*u;
	t_env	*env;
	t_token	*first_token;
	t_pipe	*pipes;
}	t_bash;

/*---------------------------------------------------------------------------*/

/* args.c */
int		ft_count_args(t_token *token);
void	ft_cpy_args(t_pipe *pipe);
void	ft_get_args(t_bash *bash);

/* builtins.c */
int		ft_is_builtin(char *cmd);
void	ft_dispatch_builtins(t_pipe *pipe, t_bash *bash);
void	ft_close_int_fd(void);
void	ft_close_all_fd(void);

/* cd.c */
void	ft_cd_msg_err(char *str, t_bash *bash);
void	ft_update_old_pwd(t_bash *bash, char *old);
void	ft_update_pwd(t_bash *bash, char *old, char buf[MAX_LINE_LEN]);
int		ft_check_cd_args(t_token *token, t_bash *bash);
void	ft_cd(t_pipe *pipe, t_bash *bash, char *old, char buf[MAX_LINE_LEN]);

/* cleaning.c */
void	ft_free_bash_env(t_bash *bash);
void	ft_free_env(t_bash *bash);
void	ft_free_tokens(t_token *token);
void	ft_free_pipes(t_bash *bash);
void	ft_free_all(t_bash *bash, bool last);

/* commands.c */
int		ft_check_cmd_2(t_bash *bash, t_pipe *pipe);
int		ft_check_cmd(t_bash *bash, t_pipe *pipe);
void	ft_cmd_err(t_pipe *list, t_bash *bash);
int		ft_is_it_exec(t_bash *bash, t_pipe *list);
int		ft_check_cmd_exec(t_bash *bash, t_pipe *list);

/* dollars_utils.c */
int		ft_which_doll_case(char *str, size_t *i, int qt);
char	*ft_manage_doll(char *str, size_t *i, t_bash *bash, int qt);
char	*ft_manage_doll_2(char *str, size_t *i, t_bash *bash, size_t k);
char	*ft_is_var(t_bash *bash, char *str);
void	ft_quotes_doll(t_bash *bash);

/* echo.c */
void	ft_convert_err(t_bash *bash);
int		ft_is_nl_option(char *str);
void	ft_echo(t_pipe *pipe);

/* env.c */
void	ft_wrong_identifier(char *str, t_bash *bash);
void	ft_cpy_envp(t_bash *bash, char **cpy);
void	ft_env(t_bash *bash, t_pipe *pipe, bool export);

/* err.c */
int		ft_err_echo_dir(t_pipe *pipe, t_bash *bash);
int		ft_check_export(char *str);
void	ft_clean_err(t_bash *bash);
void	ft_err_no_exec(char *cmd, t_bash *bash);
void	ft_fd_in_err_no(t_token *token, t_bash *bash);

/* executable.c */
int		ft_executable(t_bash *bash, t_pipe *pipe);
int		ft_executable_2(t_pipe *pass, t_bash *bash);
char	*ft_executable_3(char *cmd);
char	*ft_delete_dir(char *cwd);

/* execute.c */
void	ft_check_exec(t_bash *bash, t_pipe *list, int *comp, int *err);
char	*ft_get_exec_path(char **paths, char *cmd);
int		ft_get_nb_of_files(char **directories, DIR *dir, struct dirent *entry);
void	ft_copy_exec(t_bash *bash, char **paths, DIR *dir, \
	struct dirent *entry);
void	ft_get_exec(t_bash *bash);

/* exit.c */
int		ft_is_str_num(char *s);
void	ft_exit(t_pipe *pipe);

/* expand_heredoc.c */
char	*ft_expand_heredoc(char *line, t_bash *bash, int quotes);
char	*ft_expand_heredoc_2(char *final_str, char *line, int *i, t_bash *bash);
char	*ft_expand_heredoc_3(char *line, int *i, char *temp2, t_bash *bash);
char	*ft_expand_heredoc_4(int *i, char *temp2, t_bash *bash);

/* export.c */
void	ft_update_env(t_bash *bash, char *key, char *value, int p);
void	ft_export_new_env(t_bash *bash, char *key, char *value);
void	ft_create_env(t_bash *bash, char *key, char *value);
void	ft_dispatch_exporting(t_bash *bash, char *str, int i, int p);
int		ft_export(t_pipe *pipe, t_bash *bash);

/* fd.c */
void	ft_dup_fds(t_pipe *pipe);
void	ft_close_fds(t_pipe *pipe);
void	ft_update_fdout(t_pipe *pipe, t_token *token);
int		ft_update_fd_in_out(t_pipe *pipe, t_bash *bash, t_token *token);
int		ft_update_fds(t_bash *bash);

/* fork.c */
char	*ft_get_path_str(char *cmd, t_bash *bash);
char	**ft_join_args(t_pipe *pipe);
void	ft_execute_cmd(t_pipe *pipe, t_bash *bash);
void	ft_execute_no_pipe(t_bash *bash, t_pipe *pass);
void	ft_forking(t_bash *bash);

/* heredoc.c */
char	*ft_unquote_delim(char *delim);
int		ft_is_there_dolls(char *line);
void	ft_eof_heredoc(char *unquoted, char *filename, int fd);
int		ft_fork_heredoc(char *filename, int quotes, char *unquoted, int fd);
int		ft_heredoc(t_pipe *pipe, char *delim);

/* initialize.c */
void	ft_new_env(t_bash *bash, char *key, char *string);
void	ft_create_first_env(t_bash *bash);
void	ft_get_env(t_bash *bash, char **envp);
void	ft_cpy_env(t_bash *bash, char **envp);
void	ft_initialize_bash(t_bash *bash, char **envp, bool first);

/* norme.c */
void	ft_norme_pipe_1(t_bash *bash);
void	ft_norme_pipe_2(t_bash *bash);
int		ft_check_twice_redir(t_bash *bash);

/* parse_utils.c */
int		ft_is_token_sep(t_token *token);
char	*ft_cpy_from_input(t_bash *bash, size_t i, size_t j);
int		ft_is_just_spaces(char *input);
void	ft_trim_quotes(t_token *new);
void	ft_free_split(char **split);

/* pipe_creation.c */
void	ft_create_first_pipe(t_bash *bash);
void	ft_add_back_token(t_pipe *pipe, t_token *token);
void	ft_create_new_pipe(t_bash *bash, t_token *token);
int		ft_count_pipes(t_token *first);
void	ft_create_pipe_list(t_bash *bash);

/* pipe_exec.c */
void	ft_dup_middle_pipe(t_pipe *pass);
void	ft_wait_child(t_bash *bash, int i, int j);
void	ft_pipe(t_bash *bash, int i, t_pipe *pass, int k);
void	ft_pipe_2(t_pipe *pass, t_bash *bash, int i);
void	init_pipe(int i, t_pipe *pass);

/* pipe_utils.c */
void	ft_assign_cmd(t_pipe *next, t_token *lst, int *chev, int *cmd);
int		nb_pipes(t_pipe *pass);
void	ft_close(t_bash *bash, int i);
void	ft_fork_pipe(t_bash *bash, int i, t_pipe *pass);

/* print.c */
void	ft_print_tokens(t_bash *bash);
void	ft_print_env(t_bash *bash, char *key);
void	ft_print_pipes(t_bash *bash);
void	ft_print_envp(t_bash *bash, char *key);

/* prompt.c */
void	ft_heredoc_loop(char *unquoted, int quotes, int fd, char *filename);
void	ft_prompt_2(t_bash *bash);
void	ft_prompt(t_bash *bash, char **envp, bool first, bool last);

/* pwd.c */
void	ft_pwd(void);

/* quotes_dollars.c */
char	*ft_is_quotes_5(char *s, size_t *i, t_bash *bash, int condition);
char	*ft_is_quotes_4(char *temp, char *temp2);
char	*ft_is_quotes_3(size_t i, char *final_str);
void	ft_is_quotes_2(char s, int *sgl, int *dbl, int *sgl_first);
char	*ft_is_quotes(char *str, t_bash *bash, int sgl, int dbl);

/* quotes_utils.c */
char	*ft_dbl_quotes(char *str, size_t *i, t_bash *bash, char *final_str);
char	*ft_sgl_quotes(char *str, size_t *i, char *final_str);
int		ft_count(char *str, int i);
int		ft_count_quotes(char *str);
size_t	ft_index_closing_quote(char *str, size_t i);

/* quotes.c */
int		ft_check_quotes(t_bash *bash);
int		ft_are_there_quotes(char *input);
size_t	ft_ignore_quotes(char *str, size_t i);
int		ft_analyze_quotes(t_bash *bash);

/* signals.c */
void	ft_check_signal_exit(t_bash *bash);
void	heredoc_handler(int signum);
void	ctrl_handler(int signum);
void	ft_sig_quit(int signum);
void	ft_handle_signals(int quit);

/* token_check.c */
int		ft_check_first_and_last_token(t_token *token, t_bash *bash);
int		ft_check_middle_tokens(t_token *token, t_bash *bash);
int		ft_check_tokens(t_bash *bash);
void	ft_type_io(t_bash *bash);
int		ft_do_we_pipe(t_bash *bash);

/* token_creation.c */
void	ft_create_first_token(t_bash *bash);
t_token	*ft_first_token(t_token *token);
t_token	*ft_last_token(t_token *token);
void	ft_get_token_type(t_token *new);
void	ft_new_token(t_bash *bash, size_t j, size_t i);

/* tokenize.c */
size_t	ft_gather_trim(t_bash *bash, char *trim, size_t j, size_t k);
void	ft_token_separators(t_bash *bash, char *trim, size_t j);
void	ft_unquoting(char *token, char *str);
void	ft_unquote_tokens(t_bash *bash);
int		ft_tokenize(t_bash *bash);

/* unset.c */
void	ft_unset_cpy_envp(t_bash *bash, char **cpy, char *str);
void	ft_unset_envp(t_bash *bash, char *str);
void	ft_unset_env(t_bash *bash, char *str);
int		ft_check_unset(char *str);
void	ft_unset(t_pipe *pipe, t_bash *bash);

#endif
