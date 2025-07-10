/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snataraj <snataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:11:39 by snataraj          #+#    #+#             */
/*   Updated: 2025/05/29 11:56:32 by snataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir_in(char *filename);
static void	handle_redir_out(char *filename);
static void	handle_redir_append(char *filename);
static void	handle_heredoc(char *delimiter);

void	apply_redirs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN)
			handle_redir_in(redir->filename);
		else if (redir->type == REDIR_OUT)
			handle_redir_out(redir->filename);
		else if (redir->type == REDIR_APPEND)
			handle_redir_append(redir->filename);
		else if (redir->type == REDIR_HEREDOC)
			handle_heredoc(redir->filename);
		redir = redir->next;
	}
}

static void	handle_redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_redir_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}
