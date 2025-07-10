/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:00:09 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/02 11:24:06 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Sets up stdin/stdout redirection for a pipeline child process
static void	setup_child_redirection(t_cmd *cmd, t_pipeinfo *pinfo)
{
	dup2(pinfo->in_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pinfo->pipefd[1], STDOUT_FILENO);
	close(pinfo->pipefd[0]);
	close(pinfo->pipefd[1]);
}

// Manages parent process actions: closing fds and waiting
static void	handle_parent_pipe(t_pipeinfo *pinfo)
{
	close(pinfo->pipefd[1]);
	if (pinfo->in_fd != STDIN_FILENO)
		close(pinfo->in_fd);
	pinfo->in_fd = pinfo->pipefd[0];
}

// Waits for all child processes to finish
static void	wait_for_all_children(int *last_status)
{
	int	status;

	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
	}
}

// Forks a command in the pipeline
static void	fork_pipeline_cmd(t_cmd *cmd, t_pipeinfo *pinfo, t_mini *mini,
		char **envp)
{
	pid_t	pid;

	if (pipe(pinfo->pipefd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		setup_child_redirection(cmd, pinfo);
		run_exec_or_builtin(cmd, envp, mini);
	}
	handle_parent_pipe(pinfo);
}

// Executes a pipeline of commands
void	exec_pipeline(t_cmd *cmds, char **envp, t_mini *mini)
{
	t_pipeinfo	pinfo;

	pinfo.in_fd = STDIN_FILENO;
	while (cmds)
	{
		fork_pipeline_cmd(cmds, &pinfo, mini, envp);
		cmds = cmds->next;
	}
	wait_for_all_children(&mini->exit_status);
}
