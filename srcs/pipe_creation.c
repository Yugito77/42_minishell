/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:50:26 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/26 14:12:59 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_create_first_pipe(t_bash *bash)
{
	bash->pipes = ft_calloc(1, sizeof(t_pipe));
	if (!bash->pipes)
		return ;
	bash->pipes->cmd = ft_strdup(" === BEG OF PIPES === ");
	bash->pipes->args = NULL;
	bash->pipes->first_token = NULL;
	bash->pipes->next = NULL;
	bash->pipes->previous = NULL;
}

void	ft_add_back_token(t_pipe *pipe, t_token *token)
{
	t_token	*cpy;
	t_token	*last;

	cpy = ft_calloc(1, sizeof(t_token));
	if (!cpy)
		return ;
	last = pipe->first_token;
	cpy->str = ft_strdup(token->str);
	cpy->type = token->type;
	cpy->next = NULL;
	if (last)
	{
		while (last->next)
			last = last->next;
		last->next = cpy;
		cpy->previous = last;
	}
	else
	{
		pipe->first_token = cpy;
		cpy->previous = NULL;
	}
}

void	ft_create_new_pipe(t_bash *bash, t_token *token)
{
	t_pipe	*pipe;
	t_pipe	*next;

	pipe = ft_calloc(1, sizeof(t_pipe));
	if (!pipe)
		return ;
	pipe->cmd = NULL;
	pipe->args = NULL;
	pipe->next = NULL;
	pipe->fdin = 0;
	pipe->fdout = 1;
	pipe->cmd_ok = 1;
	next = bash->pipes;
	while (next->next)
		next = next->next;
	pipe->previous = next;
	next->next = pipe;
	pipe->first_token = NULL;
	while (token && token->type != T_PIPE)
	{
		ft_add_back_token(pipe, token);
		token = token->next;
	}
}

int	ft_count_pipes(t_token *first)
{
	t_token	*count;
	int		c;

	c = 0;
	count = first;
	while (count)
	{
		if (count->type == T_PIPE)
			c++;
		count = count->next;
	}
	return (c);
}

void	ft_create_pipe_list(t_bash *bash)
{
	t_token	*token;
	int		count;

	token = bash->first_token->next;
	count = ft_count_pipes(token) + 1;
	while (count)
	{
		if (token)
		{
			ft_create_new_pipe(bash, token);
			while (token->next && token->type != T_PIPE)
				token = token->next;
			if (token->type == T_PIPE)
				token = token->next;
		}
		count--;
	}
}
