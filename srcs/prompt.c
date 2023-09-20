/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:42:27 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/28 16:08:06 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

void	ft_heredoc_loop(char *unquoted, int quotes, int fd, char *filename)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			ft_eof_heredoc(unquoted, filename, fd);
		line = ft_expand_heredoc(line, &g_bash, quotes);
		if (!ft_strcmp(line, unquoted))
			break ;
		write(fd, line, ft_strlen(line) * sizeof(char));
		write(fd, "\n", 1);
		free(line);
	}
}

void	ft_check_last_pipe(t_bash *bash)
{
	t_pipe	*pipe;

	pipe = bash->pipes->next;
	while (pipe->next)
		pipe = pipe->next;
	if (pipe && pipe->cmd_ok == 2)
		bash->err = 127;
}

void	ft_prompt_2(t_bash *bash)
{
	int	i;

	if (!ft_is_just_spaces(bash->input))
	{
		if (ft_tokenize(bash))
		{
			i = ft_update_fds(bash);
			if (i == 2)
				return ;
			else if (!i)
				ft_forking(bash);
			ft_check_last_pipe(bash);
		}
	}
}

void	ft_prompt(t_bash *bash, char **envp, bool first, bool last)
{
	while (1)
	{
		bash->echo = 0;
		ft_initialize_bash(bash, envp, first);
		first = false;
		ft_handle_signals(0);
		bash->input = readline("minishell ~ ");
		if (!bash->input)
			ft_free_all(bash, true);
		if (ft_strcmp(bash->input, ""))
			add_history(bash->input);
		ft_prompt_2(bash);
		bash->first_token = ft_first_token(bash->first_token);
		ft_free_all(bash, last);
	}
	last = true;
	ft_free_all(bash, last);
}
