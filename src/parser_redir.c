/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:10:40 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/02 12:36:31 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*parse_redir(t_token **tokens)
{
	t_redir	*r;

	if (!tokens || !*tokens)
		return (NULL);
	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	if ((*tokens)->value[0] == '>' && (*tokens)->value[1] == '>')
		r->type = REDIR_APPEND;
	else if ((*tokens)->value[0] == '<' && (*tokens)->value[1] == '<')
		r->type = REDIR_HEREDOC;
	else if ((*tokens)->value[0] == '<')
		r->type = REDIR_IN;
	else
		r->type = REDIR_OUT;
	*tokens = (*tokens)->next;
	if (check_redir_syntax_error(tokens, r))
		return (NULL);
	r->filename = ft_strdup((*tokens)->value);
	r->next = NULL;
	*tokens = (*tokens)->next;
	return (r);
}

void	parse_cmd_node(t_cmd *node, t_token **tokens)
{
	int	argc;

	argc = 0;
	node->args = malloc(sizeof(char *) * 1024);
	if (!node->args)
		return ;
	node->redir = NULL;
	while (*tokens && (*tokens)->value[0] != '|')
	{
		if ((*tokens)->value[0] == '<' || (*tokens)->value[0] == '>')
		{
			if (!add_redirection(node, tokens))
				return ;
		}
		else
			add_argument(node, tokens, &argc);
	}
	node->args[argc] = NULL;
	if (argc > 0)
		node->cmd = node->args[0];
	else
		node->cmd = NULL;
}

void	free_redirs(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->filename);
		free(redir);
		redir = next;
	}
}

void	free_args(char **args)
{
	if (!args)
		return ;
	free(args);
}

int	add_redirection(t_cmd *node, t_token **tokens)
{
	t_redir	*r;

	r = parse_redir(tokens);
	if (!r)
	{
		free(node->args);
		node->args = NULL;
		return (0);
	}
	r->next = node->redir;
	node->redir = r;
	return (1);
}
