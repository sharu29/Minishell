/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:07:39 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/28 17:36:51 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// is_builtin: checks if the command name matches a supported builtin
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0);
}

// run_builtin: executes the matching builtin function
// env passed by reference for builtins that modify it (cd, export, unset)
int	run_builtin(t_cmd *cmd, char ***env)
{
	if (!cmd || !cmd->cmd)
		return (1);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (builtin_echo(cmd->args));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (builtin_cd(cmd->args, env));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (builtin_env(*env));
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (builtin_exit(cmd->args));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (builtin_export(cmd->args, env));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (builtin_unset(cmd->args, env));
	return (1);
}
