/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:10:49 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/02 12:43:32 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

// Create a new command node
static t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	is_invalid_pipe(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->value[0] == '|')
		{
			if (!prev || !tokens->next || tokens->next->value[0] == '|')
			{
				write(2, "minishell: syntax error near unexpected token `|'\n",
					50);
				return (1);
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}

// Parse tokens into command list
// Handles simple pipeline splitting, assigns args to t_cmd
// Redirection support is planned but not included yet

// Main parsing function

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*node;

	head = NULL;
	current = NULL;
	if (is_invalid_pipe(tokens))
		return (NULL);
	while (tokens)
	{
		node = new_cmd_node();
		parse_cmd_node(node, &tokens);
		if (!head)
			head = node;
		else
			current->next = node;
		current = node;
		if (tokens && tokens->value[0] == '|')
			tokens = tokens->next;
	}
	return (head);
}

// strings are reused from tokens
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free_redirs(cmd->redir);
		free_args(cmd->args);
		free(cmd);
		cmd = next;
	}
}

void	add_argument(t_cmd *node, t_token **tokens, int *argc)
{
	node->args[(*argc)++] = (*tokens)->value;
	*tokens = (*tokens)->next;
}
