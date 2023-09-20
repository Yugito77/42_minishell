/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:27:31 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 13:00:07 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_args(t_token *token)
{
	t_token	*arg;
	int		count;

	count = 0;
	if (!token)
		return (count);
	arg = token->next;
	while (arg && arg->type == T_STR)
	{
		count++;
		arg = arg->next;
	}
	return (count);
}

void	ft_cpy_args(t_pipe *pipe)
{
	t_token	*token;
	int		args_count;
	int		i;

	token = pipe->first_token;
	while (token->type != T_CMD && token->next)
		token = token->next;
	args_count = ft_count_args(token);
	if (args_count)
	{
		pipe->args = ft_calloc(args_count + 1, sizeof(char *));
		if (!pipe->args)
			return ;
		i = 0;
		token = token->next;
		while (i < args_count)
		{
			pipe->args[i] = ft_strdup(token->str);
			if (!pipe->args[i])
				return ;
			token = token->next;
			i++;
		}
	}
}

void	ft_get_args(t_bash *bash)
{
	t_pipe	*pipe;

	pipe = bash->pipes->next;
	while (pipe)
	{
		if (pipe->first_token)
			ft_cpy_args(pipe);
		pipe = pipe->next;
	}
}
