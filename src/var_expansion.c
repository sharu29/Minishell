/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:12:37 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/29 11:56:23 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

// Searches the environment for the given variable name
// Returns a copy of the value if found, or NULL
static char	*get_env_value(const char *name, char **env)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

// Expands the $? special variable
static void	expand_exit_status(t_expander *e)
{
	char	*code;

	code = ft_itoa(e->mini->exit_status);
	append_str(e->result, &e->j, code);
	free(code);
	e->i++;
}

// Expands regular variables like $USER
static void	expand_named_variable(t_expander *e)
{
	int		start;
	char	*val;
	char	tmp;

	start = e->i;
	while (is_valid_var_char(e->input[e->i]))
		e->i++;
	tmp = ((char *)e->input)[e->i];
	((char *)e->input)[e->i] = '\0';
	val = get_env_value(&e->input[start], e->mini->env);
	((char *)e->input)[e->i] = tmp;
	if (val)
	{
		append_str(e->result, &e->j, val);
		free(val);
	}
}

// Handles any variable expansion after a '$'
static void	expand_variable(t_expander *e)
{
	e->i++;
	if (e->input[e->i] == '?')
		expand_exit_status(e);
	else
		expand_named_variable(e);
}

// Main entry point: expands variables in input
char	*expand_variables(const char *input, t_mini *mini)
{
	t_expander	e;

	e.input = input;
	e.i = 0;
	e.j = 0;
	e.result = malloc(4096);
	e.mini = mini;
	while (e.input[e.i])
	{
		if (e.input[e.i] == '$' && e.input[e.i + 1])
			expand_variable(&e);
		else
			e.result[e.j++] = e.input[e.i++];
	}
	e.result[e.j] = '\0';
	return (e.result);
}
