/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:46:00 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/29 11:56:21 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Appends a string to the result buffer, updating the current index
void	append_str(char *buf, int *j, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		buf[(*j)++] = str[i++];
}

// Returns true if c is a valid character in a variable name (A-Z, a-z, 0-9, _)
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
