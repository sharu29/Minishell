/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:11:26 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/02 12:00:32 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static char	*get_input(t_mini *mini)
{
	char	*input;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	input = readline("minishell$ ");
	if (g_sig == SIGINT)
	{
		mini->exit_status = g_sig + 128;
		g_sig = 0;
	}
	return (input);
}

static int	handle_empty_input(char *input)
{
	if (!input)
		return (-1);
	if (input[0] == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

int	ft_prompt(t_mini *mini)
{
	char	*input;
	char	*expanded;
	int		empty_check;

	input = get_input(mini);
	empty_check = handle_empty_input(input);
	if (empty_check != 0)
		return (empty_check);
	if (check_unclosed_quotes(input))
	{
		free(input);
		return (1);
	}
	add_history(input);
	expanded = expand_variables(input, mini);
	ft_run_command(mini, input, expanded);
	return (mini->exit_status);
}

void	ft_run_command(t_mini *mini, char *input, char *expanded)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(expanded);
	free(input);
	free(expanded);
	mini->token_list = tokens;
	cmds = parse_tokens(tokens);
	if (!cmds)
	{
		free_tokens(tokens);
		mini->token_list = NULL;
		return ;
	}
	mini->cmd_list = cmds;
	execute_cmds(cmds, mini->env, mini);
	free_tokens(tokens);
	free_cmd_list(cmds);
	mini->token_list = NULL;
	mini->cmd_list = NULL;
}

/* static void	print_commands(t_cmd *cmds)
{
	t_cmd	*c;
	int		i;

	c = cmds;
	while (c)
	{
		i = 0;
		printf("CMD: %s\n", c->cmd);
		while (c->args && c->args[i])
		{
			printf("  ARG[%d]: %s\n", i, c->args[i]);
			i++;
		}
		c = c->next;
	}
} */
// print_commands(cmds);