/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:21:56 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/06 14:29:21 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_gather_trim(t_bash *bash, char *trim, size_t j, size_t k)
{
	size_t	l;

	l = k;
	while (1)
	{
		while (trim[l] && trim[l] != SGL_QT && trim[l] != DBL_QT
			&& trim[l] != RED_I && trim[l] != RED_O && trim[l] != PIPE)
			l++;
		if (trim[l] == SGL_QT || trim[l] == DBL_QT)
			l = ft_ignore_quotes(trim, l);
		if (trim[l] == PIPE || trim[l] == RED_I || trim[l] == RED_O
			|| l == ft_strlen(trim))
			break ;
	}
	ft_new_token(bash, j + k, j + l);
	return (l);
}

void	ft_token_separators(t_bash *bash, char *trim, size_t j)
{
	size_t	k;

	k = 0;
	while (k < ft_strlen(trim))
	{
		if ((trim[k] == RED_I && trim[k + 1] == RED_I)
			|| (trim[k] == RED_O && trim[k + 1] == RED_O))
		{
			ft_new_token(bash, j + k, j + k + 2);
			k += 2;
		}
		else if (trim[k] == PIPE || trim[k] == RED_I || trim[k] == RED_O)
		{
			ft_new_token(bash, j + k, j + k + 1);
			k++;
		}
		else
			k = ft_gather_trim(bash, trim, j, k);
	}
}

void	ft_unquoting(char *token, char *str)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == SGL_QT || str[i] == DBL_QT)
		{
			k = ft_index_closing_quote(str, i);
			i++;
			while (i < k)
			{
				token[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
		else
			token[j++] = str[i++];
	}
}

void	ft_unquote_tokens(t_bash *bash)
{
	t_token	*pass;
	char	*token;
	size_t	l;

	pass = bash->first_token->next;
	while (pass)
	{
		if (pass->previous->type == T_RED_I_DBL)
			pass = pass->next;
		else
		{
			l = ft_strlen(pass->str) - ft_count_quotes(pass->str) + 1;
			token = ft_calloc(l, sizeof(char));
			if (!token)
				return ;
			ft_unquoting(token, pass->str);
			free(pass->str);
			pass->str = ft_strdup(token);
			free(token);
			pass = pass->next;
		}
	}
}

int	ft_tokenize(t_bash *bash)
{
	size_t	i;
	size_t	j;
	char	*trim;
	char	*cpy;

	i = 0;
	if (!ft_analyze_quotes(bash))
		return (0);
	ft_quotes_doll(bash);
	while (i < ft_strlen(bash->input) && bash->input != NULL)
	{
		j = i;
		while (bash->input[i] != ' ' && i < ft_strlen(bash->input))
			i = ft_ignore_quotes(bash->input, i);
		cpy = ft_cpy_from_input(bash, i, j);
		trim = ft_strtrim(cpy, " ");
		if (ft_strcmp(trim, ""))
			ft_token_separators(bash, trim, j);
		free(trim);
		free(cpy);
		i++;
	}
	ft_unquote_tokens(bash);
	return (ft_do_we_pipe(bash));
}
