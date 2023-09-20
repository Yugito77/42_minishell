/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:23:42 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/27 23:35:01 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_assign_cmd(t_pipe *next, t_token *lst, int *chev, int *cmd)
{
	while (lst && !(*cmd))
	{
		if ((!lst->previous) && lst->type == T_STR)
		{
			lst->type = T_CMD;
			next->cmd = ft_strdup(lst->str);
			*cmd = 1;
		}
		else if ((!lst->previous) && lst->type != T_STR)
			*chev = 1;
		else if (*chev == 1 && (lst->previous->type == T_INPUT
				|| lst->previous->type == T_OUTPUT
				|| lst->previous->type == T_APPEND
				|| lst->previous->type == T_HEREDOC) && \
			lst->previous->previous->type != T_STR && lst->type == T_STR)
		{
			lst->type = T_CMD;
			next->cmd = ft_strdup(lst->str);
			*cmd = 1;
		}
		lst = lst->next;
	}
}

int	nb_pipes(t_pipe *pass)
{
	int	i;

	i = 0;
	while (pass->next)
	{
		i++;
		pass = pass->next;
	}
	return (i);
}

void	ft_close(t_bash *bash, int i)
{
	int		j;
	t_pipe	*pass;

	pass = bash->pipes->next;
	j = 0;
	while (j < i)
	{
		close(pass->fd[0]);
		close(pass->fd[1]);
		pass = pass->next;
		j++;
	}
}

void	ft_fork_pipe(t_bash *bash, int i, t_pipe *pass)
{
	ft_handle_signals(0);
	ft_close(bash, i);
	ft_get_args(bash);
	if (ft_is_builtin(pass->cmd))
	{
		ft_dispatch_builtins(pass, bash);
		ft_free_all(bash, false);
		ft_free_env(bash);
		ft_close_all_fd();
		exit(bash->err);
	}
	else if (pass->cmd)
		ft_execute_cmd(pass, bash);
}
