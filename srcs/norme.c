/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:32:07 by benjamin          #+#    #+#             */
/*   Updated: 2022/07/28 16:32:34 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_norme_pipe_1(t_bash *bash)
{
	ft_putstr_fd("\n", 2);
	bash->err = 130;
}

void	ft_norme_pipe_2(t_bash *bash)
{
	ft_putstr_fd("Quit (core dumped)\n", 2);
	bash->err = 131;
}

int	ft_check_twice_redir(t_bash *bash)
{
	t_token	*token;

	token = bash->first_token->next;
	while (token)
	{
		if ((token->type == '>' || token->type == '<' || token->type == '@'
				|| token->type == '?') && token->next
			&& (token->next->type == '>' || token->next->type == '<'
				|| token->next->type == '@' || token->next->type == '?'))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", \
			token->next->str);
			bash->err = 2;
			return (1);
		}
		token = token->next;
	}
	return (0);
}
