/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:10:18 by snataraj          #+#    #+#             */
/*   Updated: 2025/06/01 13:56:12 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int			g_sig = 0;

void	init_mini(t_mini *mini, char **env)
{
	mini->token_list = NULL;
	mini->cmd_list = NULL;
	mini->exit_status = 0;
	mini->env = dup_array(env);
	mini->pids = NULL;
	mini->pipes = NULL;
}

static void	cleanup_shell(t_mini *mini)
{
	if (mini->cmd_list)
		free_cmd_list(mini->cmd_list);
	if (mini->token_list)
		free_tokens(mini->token_list);
	free_array(mini->env);
	rl_clear_history();
	clear_history();
}

int	main(int argc, char *argv[], char *env[])
{
	t_mini	mini;
	int		stdin;
	int		stdout;

	g_sig = 0;
	(void)argv;
	(void)argc;
	if (argc != 1)
		return (ft_putstr_fd("Error: Invalid arguments\n", 0), 1);
	init_mini(&mini, env);
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	while (1)
	{
		dup2(stdin, 0);
		dup2(stdout, 1);
		if (ft_prompt(&mini) == -1)
			break ;
	}
	write(1, "exit\n", 5);
	cleanup_shell(&mini);
	return (0);
}
