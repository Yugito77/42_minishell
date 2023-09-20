/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:03:14 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/27 19:02:19 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

void	ft_dispatch_builtins(t_pipe *pipe, t_bash *bash)
{
	char	buf[MAX_LINE_LEN];
	char	*old;

	old = getcwd(buf, MAX_LINE_LEN);
	if (!ft_strcmp(pipe->cmd, "echo"))
		ft_echo(pipe);
	else if (!ft_strcmp(pipe->cmd, "cd"))
		ft_cd(pipe, bash, old, buf);
	else if (!ft_strcmp(pipe->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(pipe->cmd, "export"))
	{
		if (ft_export(pipe, bash))
			ft_env(bash, pipe, true);
	}
	else if (!ft_strcmp(pipe->cmd, "unset"))
		ft_unset(pipe, bash);
	else if (!ft_strcmp(pipe->cmd, "env"))
		ft_env(bash, pipe, false);
	else if (!ft_strcmp(pipe->cmd, "exit"))
		ft_exit(pipe);
}

void	ft_close_int_fd(void)
{
	int	i;

	i = 2;
	close(0);
	close(1);
	while (i < 1024)
	{
		if (!read(i, 0, 0))
			close(i);
		i++;
	}
}

void	ft_close_all_fd(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}
