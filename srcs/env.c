/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:00:57 by benjamin          #+#    #+#             */
/*   Updated: 2022/07/27 22:24:15 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_wrong_identifier(char *str, t_bash *bash)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	bash->err = 1;
}

void	ft_cpy_envp(t_bash *bash, char **cpy)
{
	int		i;

	i = 0;
	while (bash->envp[i])
	{
		cpy[i] = ft_strdup(bash->envp[i]);
		free(bash->envp[i]);
		i++;
	}
	free(bash->envp);
	bash->envp = ft_calloc(i + 2, sizeof(char *));
	if (!bash->envp)
		return ;
}

void	ft_env(t_bash *bash, t_pipe *pipe, bool export)
{
	int	i;

	i = 0;
	if (pipe->args)
	{
		ft_putstr_fd("this command does not take arguments\n", 2);
		return ;
	}
	while (bash->envp[i])
	{
		if (export)
			ft_putstr_fd("export ", 1);
		ft_putstr_fd(bash->envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
