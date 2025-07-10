/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:09:39 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/28 17:25:16 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env: prints each environment variable in the env array
int	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	builtin_export(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		replace_or_append_env(args[i], env);
		i++;
	}
	return (0);
}

int	count_env_vars(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	remove_env_var(char *name, char ***env)
{
	int		i;
	int		j;
	int		len;
	int		count;
	char	**new_env;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	count = count_env_vars(*env);
	new_env = malloc(sizeof(char *) * (count + 1));
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, len) == 0 && (*env)[i][len] == '=')
			free((*env)[i]);
		else
			new_env[j++] = (*env)[i];
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
}
