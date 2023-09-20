/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:04:31 by benjamin          #+#    #+#             */
/*   Updated: 2022/06/15 13:10:23 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

void	ft_pwd(void)
{
	char	buf[MAX_LINE_LEN];
	char	*cwd;

	cwd = getcwd(buf, MAX_LINE_LEN);
	if (!cwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd(" cannot access parent directories: No such file", 2);
		ft_putstr_fd(" or directory\n", 2);
		g_bash.err = 1;
		return ;
	}
	cwd = ft_strjoin(cwd, "\n");
	ft_putstr_fd(cwd, 1);
	free(cwd);
	g_bash.err = 0;
}
