/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:50:09 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/02 12:44:54 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int			g_sig;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;
typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;
typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}					t_token;
typedef struct s_mini
{
	char			**env;
	char			*err_msg;
	int				exit_status;
	int				**pipes;
	int				**pids;
	t_token			*token_list;
	t_cmd			*cmd_list;
}					t_mini;
typedef struct s_expander
{
	const char		*input;
	int				i;
	int				j;
	char			*result;
	t_mini			*mini;
}					t_expander;
typedef struct s_pipefd
{
	int				in;
	int				out;
}					t_pipefd;
typedef struct s_pipeinfo
{
	int				pipefd[2];
	int				in_fd;
	int				status;
}					t_pipeinfo;

// main.c
void				init_mini(t_mini *mini, char **env);

// prompt.c
int					ft_prompt(t_mini *mini);
void				ft_run_command(t_mini *mini, char *input, char *expanded);

// array.c
char				**dup_array(char **arr);
void				free_array(char **arr);

// signal.c
void				sig_handler(int sig);
void				sigint_void(int sig);

// lexer.c
t_token				*lexer(const char *input);
void				free_tokens(t_token *tok);

// parser.c
t_cmd				*parse_tokens(t_token *tokens);
void				free_cmd_list(t_cmd *cmd);

// parser_redir.c
t_redir				*parse_redir(t_token **tokens);
void				parse_cmd_node(t_cmd *node, t_token **tokens);
void				free_redirs(t_redir *redir);
void				free_args(char **args);
int					add_redirection(t_cmd *node, t_token **tokens);

// executor.c
void				execute_cmds(t_cmd *cmds, char **envp, t_mini *mini);
void				run_exec_or_builtin(t_cmd *cmd, char **envp, t_mini *mini);
void				exec_pipeline(t_cmd *cmds, char **envp, t_mini *mini);

// utils_cmd_path.c
char				*get_cmd_path(char *cmd, char **envp);
char				*ft_strjoin_three(char *s1, char *s2, char *s3);
void				ft_free_split(char **arr);

// builtins2
int					builtin_env(char **env);
void				remove_env_var(char *name, char ***env);
int					count_env_vars(char **env);
void				replace_or_append_env(char *arg, char ***env);
int					builtin_export(char **args, char ***env);

// builtins1
int					builtin_echo(char **args);
int					builtin_pwd(void);
int					builtin_cd(char **args, char ***env);
int					builtin_unset(char **args, char ***env);
int					builtin_exit(char **args);

// builtins.c
int					run_builtin(t_cmd *cmd, char ***env);
int					is_builtin(char *cmd);

// redirection.c
void				apply_redirs(t_redir *redir);

// var_expansion.c
char				*expand_variables(const char *input, t_mini *mini);
void				append_str(char *buf, int *j, const char *str);
int					is_valid_var_char(char c);

// utils
int					ft_strcmp(const char *s1, const char *s2);
int					is_metachar(char c);
int					is_space(char c);
int					check_unclosed_quotes(const char *input);
void				add_argument(t_cmd *node, t_token **tokens, int *argc);
int					check_redir_syntax_error(t_token **tokens, t_redir *r);

#endif
