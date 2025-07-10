/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:06:50 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/28 17:06:56 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// to initialise the env array and stored in mini struct
// returns allocated array of strings

char	**dup_array(char **arr)
{
	int		i;
	int		j;
	char	**final_arr;

	i = 0;
	while (arr[i])
		i++;
	final_arr = malloc(sizeof(char *) * (i + 1));
	if (!final_arr)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		final_arr[j] = ft_strdup(arr[j]);
		if (!final_arr[j])
		{
			while (j > 0)
				free(final_arr[--j]);
			free(final_arr);
			final_arr = NULL;
			return (NULL);
		}
	}
	final_arr[j] = NULL;
	return (final_arr);
}

// to free the string array

void	free_array(char **arr)
{
	char	**fstr;

	if (!arr)
		return ;
	fstr = arr;
	while (*arr)
	{
		free(*arr);
		*arr = NULL;
		arr++;
	}
	free(fstr);
	fstr = NULL;
}
