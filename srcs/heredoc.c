/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:38:15 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/27 16:52:18 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

char	*ft_unquote_delim(char *delim)
{
	char	*unquoted;
	size_t	l;

	l = ft_strlen(delim) - ft_count_quotes(delim) + 1;
	unquoted = ft_calloc(l, sizeof(char));
	if (!unquoted)
		return (NULL);
	ft_unquoting(unquoted, delim);
	return (unquoted);
}

int	ft_is_there_dolls(char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (line && *line)
	{
		while (line[k + 1])
		{
			if (line[k] == '$')
				i++;
			k++;
		}
	}
	if (!i)
		return (0);
	else
		return (1);
}

void	ft_eof_heredoc(char *unquoted, char *filename, int fd)
{
	ft_putstr_fd("minishell: warning: here-document at line delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(unquoted, 2);
	ft_putstr_fd("')\n", 2);
	close(fd);
	free(unquoted);
	free(filename);
	ft_free_all(&g_bash, false);
	ft_free_env(&g_bash);
	ft_close_int_fd();
	exit(0);
}

int	ft_fork_heredoc(char *filename, int quotes, char *unquoted, int fd)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		signal(SIGINT, heredoc_handler);
		g_bash.f = filename;
		g_bash.u = unquoted;
		ft_heredoc_loop(unquoted, quotes, fd, filename);
		close(fd);
		free(unquoted);
		free(filename);
		ft_free_all(&g_bash, false);
		ft_free_env(&g_bash);
		ft_close_int_fd();
		exit(g_bash.err);
	}
	if (pid != -1 && (0 < waitpid(pid, &g_bash.err, 0)))
		g_bash.err = WEXITSTATUS(g_bash.err);
	if (WIFSIGNALED(g_bash.err) && WTERMSIG(g_bash.err) == 2)
	{
		g_bash.err = 130;
		return (1);
	}
	return (0);
}

int	ft_heredoc(t_pipe *pipe, char *delim)
{
	char	*filename;
	char	*unquoted;
	int		fd;
	int		quotes;
	int		c;

	filename = ft_strdup("h");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	g_bash.h_f = fd;
	quotes = ft_are_there_quotes(delim);
	unquoted = ft_unquote_delim(delim);
	signal(SIGINT, SIG_IGN);
	c = ft_fork_heredoc(filename, quotes, unquoted, fd);
	ft_handle_signals(0);
	if (pipe->fdin)
		close(pipe->fdin);
	pipe->fdin = open(filename, O_RDONLY);
	if (pipe->fdin == -1)
		return (0);
	free(filename);
	free(unquoted);
	close(fd);
	unlink("h");
	return (c);
}
