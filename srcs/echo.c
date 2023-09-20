/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:01:43 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/26 16:29:48 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_convert_err(t_bash *bash)
{
	while (bash->err > 255)
		bash->err = bash->err % 255;
}

int	ft_is_nl_option(char *str)
{
	size_t	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_pipe *pipe)
{
	t_token	*token;
	int		nl;

	nl = 0;
	token = pipe->first_token;
	while (token->type != T_CMD)
		token = token->next;
	if (token->next)
		token = token->next;
	if (token && ft_is_nl_option(token->str))
	{
		while (token && ft_is_nl_option(token->str))
			token = token->next;
		nl++;
	}
	while (token)
	{
		if (token->type == T_STR)
			ft_putstr_fd(token->str, 1);
		if (token->next && token->next->type == T_STR)
			ft_putstr_fd(" ", 1);
		token = token->next;
	}
	if (!nl)
		ft_putstr_fd("\n", 1);
}
