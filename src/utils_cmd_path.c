/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:12:22 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/29 11:56:27 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/stat.h>

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, s3);
	free(temp);
	return (res);
}

// Extract PATH directories from envp

static char	**extract_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

// Try appending cmd to each path and return the full path if found.

static char	*search_in_paths(char **paths, char *cmd)
{
	int			i;
	char		*full;
	struct stat	sb;

	i = 0;
	while (paths[i])
	{
		full = ft_strjoin_three(paths[i], "/", cmd);
		if (full && stat(full, &sb) == 0)
		{
			ft_free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;

	if (!cmd || cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	paths = extract_paths(envp);
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
