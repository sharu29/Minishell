/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:07:08 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/29 13:15:45 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Replaces an existing environment variable if the key matches.
// Returns 1 if a replacement was made, 0 otherwise.
static int	replace_existing_env_var(char *arg, char ***env, int key_len)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, key_len) == 0
			&& (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

// Appends a new key=value string to the environment array.
static void	append_env_var(char *arg, char ***env)
{
	int		i;
	int		count;
	char	**new_env;

	count = count_env_vars(*env);
	new_env = malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[count] = ft_strdup(arg);
	new_env[count + 1] = NULL;
	free(*env);
	*env = new_env;
}

// Main entry point: if the key in arg exists in env, replace it.
// If it doesn't exist, append the new key=value pair to env.
void	replace_or_append_env(char *arg, char ***env)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (arg[len] != '=')
		return ;
	if (!replace_existing_env_var(arg, env, len))
		append_env_var(arg, env);
}
