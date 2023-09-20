/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:13:58 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/26 14:12:56 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_cmd_2(t_bash *bash, t_pipe *pipe)
{
	int	i;

	i = ft_executable(bash, pipe);
	if (i)
		return (1);
	i = ft_check_cmd_exec(bash, pipe);
	return (i);
}

int	ft_check_cmd(t_bash *bash, t_pipe *pipe)
{
	t_token	*lst;
	int		chev;
	int		cmd;
	int		err;

	chev = 0;
	cmd = 0;
	err = 0;
	lst = pipe->first_token;
	chev = 0;
	cmd = 0;
	ft_assign_cmd(pipe, lst, &chev, &cmd);
	if (cmd)
		err = ft_check_cmd_2(bash, pipe);
	if (cmd && !err)
	{
		pipe->cmd_ok = 0;
		return (0);
	}
	return (err);
}

void	ft_cmd_err(t_pipe *list, t_bash *bash)
{
	char	*temp;

	if (!ft_strcmp("..", list->cmd))
	{
		ft_putstr_fd(list->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		bash->err = 127;
	}
	else if ((list->cmd[0] != '.' && list->cmd[0] != '/')
		|| (list->cmd[0] == '.' && list->cmd[1] != '.'
			&& list->cmd[1] != '/'))
	{
		temp = ft_strjoin(list->cmd, ": command not found\n");
		ft_putstr_fd(temp, 2);
		free(temp);
		bash->err = 127;
	}
}

int	ft_is_it_exec(t_bash *bash, t_pipe *list)
{
	int	comp;
	int	err;

	comp = 0;
	err = 0;
	if (list->cmd)
	{
		if (list->cmd[0] == '/')
			return (err);
		if (!ft_is_builtin(list->cmd))
		{
			if (bash->exec)
				ft_check_exec(bash, list, &comp, &err);
			else
			{
				ft_cmd_err(list, bash);
				err++;
			}
		}
	}
	return (err);
}

int	ft_check_cmd_exec(t_bash *bash, t_pipe *list)
{
	int		err;

	err = 0;
	err += ft_is_it_exec(bash, list);
	return (err);
}
