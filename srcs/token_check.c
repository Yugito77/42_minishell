/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:33:11 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/06 15:36:37 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_first_and_last_token(t_token *token, t_bash *bash)
{
	if (token->previous->type == T_BEG)
	{
		if (token->type == '|')
		{
			ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
			bash->err = 2;
			return (0);
		}
	}
	if (token->type == T_RED_I_SGL || token->type == T_RED_I_DBL
		|| token->type == T_RED_O_SGL || token->type == T_RED_O_DBL)
	{
		if ((token->previous->type == T_BEG && !token->next)
			|| (token->previous->type != T_BEG))
		{
			ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
			bash->err = 2;
			return (0);
		}
	}
	return (1);
}

int	ft_check_middle_tokens(t_token *token, t_bash *bash)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	if (ft_is_token_sep(token) && ft_is_token_sep(token->next))
	{
		s1 = ft_strjoin("syntar error near unexpected '", token->next->str);
		s2 = ft_strjoin(s1, "'\n");
		ft_putstr_fd(s2, 2);
		free(s1);
		free(s2);
		bash->err = 2;
		return (0);
	}
	else if ((ft_is_token_sep(token) || token->type == T_PIPE)
		&& token->next->type == T_PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		bash->err = 2;
		return (0);
	}
	return (1);
}

int	ft_check_tokens(t_bash *bash)
{
	if (ft_check_twice_redir(bash))
		return (1);
	bash->first_token = ft_first_token(bash->first_token);
	bash->first_token = bash->first_token->next;
	if (!ft_check_first_and_last_token(bash->first_token, bash))
		return (1);
	while (bash->first_token->next)
	{
		if (!ft_check_middle_tokens(bash->first_token, bash))
			return (1);
		bash->first_token = bash->first_token->next;
	}
	if (bash->first_token->previous->type != T_BEG)
		if (!ft_check_first_and_last_token(bash->first_token, bash))
			return (1);
	bash->first_token = ft_first_token(bash->first_token);
	return (0);
}

void	ft_type_io(t_bash *bash)
{
	t_token	*token;

	token = bash->first_token;
	while (token)
	{
		if (token->previous && token->previous->type == T_RED_I_DBL)
			token->type = T_HEREDOC;
		else if (token->previous && token->previous->type == T_RED_I_SGL)
			token->type = T_INPUT;
		else if (token->previous && token->previous->type == T_RED_O_DBL)
			token->type = T_APPEND;
		else if (token->previous && token->previous->type == T_RED_O_SGL)
			token->type = T_OUTPUT;
		token = token->next;
	}
}

int	ft_do_we_pipe(t_bash *bash)
{
	if (bash->first_token->next)
	{
		if (!ft_check_tokens(bash))
		{
			ft_type_io(bash);
			ft_create_pipe_list(bash);
			return (1);
		}
	}
	return (0);
}
