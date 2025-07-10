/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:10:03 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/29 13:21:30 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_quote(const char **input, char *word, int *i, char *quote)
{
	if (**input == '\"' || **input == '\'')
	{
		if (*quote == 0)
			*quote = **input;
		else if (*quote == **input)
			*quote = 0;
		else
			word[(*i)++] = **input;
		(*input)++;
	}
}

static char	*read_word(const char **input)
{
	char	*word;
	int		i;
	char	quote;

	word = malloc(1024);
	i = 0;
	quote = 0;
	while (**input && (quote || (!is_space(**input) && !is_metachar(**input))))
	{
		if (**input == '\'' || **input == '\"')
			read_quote(input, word, &i, &quote);
		else
		{
			word[i++] = **input;
			(*input)++;
		}
	}
	word[i] = '\0';
	return (word);
}

static char	*read_metachar(const char **input)
{
	char	*meta;

	meta = malloc(3);
	meta[0] = *(*input)++;
	if ((meta[0] == '<' || meta[0] == '>') && **input == meta[0])
		meta[1] = *(*input)++;
	else
		meta[1] = '\0';
	meta[2] = '\0';
	return (meta);
}

t_token	*lexer(const char *input)
{
	t_token	*head;
	t_token	*last;
	t_token	*new;

	head = NULL;
	last = NULL;
	while (*input)
	{
		while (is_space(*input))
			input++;
		if (*input == '\0')
			break ;
		new = malloc(sizeof(t_token));
		new->next = NULL;
		if (is_metachar(*input))
			new->value = read_metachar(&input);
		else
			new->value = read_word(&input);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
	}
	return (head);
}

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->value);
		free(tmp);
	}
}
