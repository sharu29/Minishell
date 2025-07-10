/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:09:50 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/02 11:28:07 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Executes a single command (not in a pipeline)
static void	exec_single_cmd(t_cmd *cmd, char **envp, t_mini *mini)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->cmd)
		return ;
	if (is_builtin(cmd->cmd) && !cmd->next)
	{
		apply_redirs(cmd->redir);
		mini->exit_status = run_builtin(cmd, &mini->env);
		return ;
	}
	pid = fork();
	if (pid == 0)
		run_exec_or_builtin(cmd, envp, mini);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
}

// Main dispatcher: runs either a single command or a pipeline
void	execute_cmds(t_cmd *cmds, char **envp, t_mini *mini)
{
	if (!cmds)
		return ;
	if (!cmds->next)
		exec_single_cmd(cmds, envp, mini);
	else
		exec_pipeline(cmds, envp, mini);
}
