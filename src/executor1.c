/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:29:37 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/01 13:56:09 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_and_exit(t_mini *mini, int status)
{
	free_cmd_list(mini->cmd_list);
	free_tokens(mini->token_list);
	free_array(mini->env);
	exit(status);
}

static void	handle_builtin_exit(t_cmd *cmd, t_mini *mini)
{
	int	status;

	status = run_builtin(cmd, &mini->env);
	cleanup_and_exit(mini, status);
}

static void	handle_execve_failure(t_mini *mini)
{
	perror("execve");
	if (errno == ENOENT)
		cleanup_and_exit(mini, 127);
	else if (errno == EACCES)
		cleanup_and_exit(mini, 126);
	else
		cleanup_and_exit(mini, 1);
}

// Restores default signals and runs builtin or execve
void	run_exec_or_builtin(t_cmd *cmd, char **envp, t_mini *mini)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	apply_redirs(cmd->redir);
	if (is_builtin(cmd->cmd))
		handle_builtin_exit(cmd, mini);
	path = get_cmd_path(cmd->cmd, envp);
	if (!path)
	{
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_and_exit(mini, 127);
	}
	if (execve(path, cmd->args, envp) == -1)
		handle_execve_failure(mini);
}
