/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:09:08 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/09 12:45:02 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_token_sep(t_token *token)
{
	if (token->type == T_RED_I_SGL || token->type == T_RED_I_DBL
		|| token->type == T_RED_O_SGL || token->type == T_RED_I_SGL)
		return (1);
	return (0);
}

char	*ft_cpy_from_input(t_bash *bash, size_t i, size_t j)
{
	char	*cpy;
	size_t	c;

	c = 0;
	cpy = calloc(i - j + 1, sizeof(char));
	if (cpy)
	{
		while (j + c < i)
		{
			cpy[c] = bash->input[j + c];
			c++;
		}
	}
	return (cpy);
}

int	ft_is_just_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	ft_trim_quotes(t_token *new)
{
	char	*temp;

	if (new->str[0] == '"')
	{
		temp = ft_strdup(new->str);
		free(new->str);
		new->str = ft_strtrim(temp, "\"");
		free(temp);
	}
	else if (new->str[0] == '\'')
	{
		temp = ft_strdup(new->str);
		free(new->str);
		new->str = ft_strtrim(temp, "\'");
		free(temp);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split[i]);
		free(split);
	}
}
