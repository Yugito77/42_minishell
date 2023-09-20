/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:00:15 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/04 15:36:20 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_create_first_token(t_bash *bash)
{
	bash->first_token = ft_calloc(1, sizeof(t_token));
	if (!bash->first_token)
		return ;
	bash->first_token->str = ft_strdup(" === BEG OF TOKENS === ");
	bash->first_token->type = T_BEG;
	bash->first_token->previous = NULL;
	bash->first_token->next = NULL;
}

t_token	*ft_first_token(t_token *token)
{
	while (token->previous)
		token = token->previous;
	return (token);
}

t_token	*ft_last_token(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

void	ft_get_token_type(t_token *new)
{
	if (!ft_strcmp(new->str, "|"))
		new->type = T_PIPE;
	else if (!ft_strcmp(new->str, ">"))
		new->type = T_RED_O_SGL;
	else if (!ft_strcmp(new->str, ">>"))
		new->type = T_RED_O_DBL;
	else if (!ft_strcmp(new->str, "<"))
		new->type = T_RED_I_SGL;
	else if (!ft_strcmp(new->str, "<<"))
		new->type = T_RED_I_DBL;
	else
		new->type = T_STR;
}

void	ft_new_token(t_bash *bash, size_t j, size_t i)
{
	t_token	*new;
	t_token	*last;
	char	*cpy;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return ;
	last = ft_last_token(bash->first_token);
	last->next = new;
	new->previous = last;
	new->next = NULL;
	cpy = ft_cpy_from_input(bash, i, j);
	new->str = ft_strtrim(cpy, " ");
	free(cpy);
	ft_get_token_type(new);
}
