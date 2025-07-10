/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:07:48 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/28 17:23:36 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Implements shell built-in commands: echo, cd, pwd, env, exit
// Provides helper functions to detect
// and execute builtins within the shell process.

// echo: prints arguments to stdout
// supports the -n flag to omit the trailing newline

// line 31: Check for -n option: do not print newline
// line 36: Print each argument separated by spaces
// line 44: Print trailing newline if not suppressed

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && args[i][0] == '-' && args[i][1] == 'n' && args[i][2] == '\0')
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

// pwd: prints the current working directory to stdout
int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

// cd: changes the shell's current directory
// If no argument, change to HOME environment variable
// If no path provided, fall back to HOME from env array
int	builtin_cd(char **args, char ***env)
{
	char	*path;
	int		i;

	path = args[1];
	if (!path || path[0] == '\0')
	{
		i = 0;
		while ((*env)[i] && ft_strncmp((*env)[i], "HOME=", 5) != 0)
			i++;
		if ((*env)[i])
			path = (*env)[i] + 5;
	}
	if (!path)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	builtin_unset(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(args[i], env);
		i++;
	}
	return (0);
}

// exit: exits the shell with optional status code
// If provided, args[1] is converted to integer status
int	builtin_exit(char **args)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	exit(status);
	return (status);
}
