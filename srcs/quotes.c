/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:00:06 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/05 18:37:07 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_quotes(t_bash *bash)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(bash->input))
	{
		if (bash->input[i] == SGL_QT || bash->input[i] == DBL_QT)
		{
			j = i;
			i++;
			while (i < ft_strlen(bash->input))
			{
				if (bash->input[i] == bash->input[j])
					break ;
				i++;
			}
			if (i == ft_strlen(bash->input))
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_are_there_quotes(char *input)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == SGL_QT || input[i] == DBL_QT)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_ignore_quotes(char *str, size_t i)
{
	if (str[i] == SGL_QT)
	{
		i++;
		while (str[i] != SGL_QT)
			i++;
		i++;
	}
	else if (str[i] == DBL_QT)
	{
		i++;
		while (str[i] != DBL_QT)
			i++;
		i++;
	}
	else if (i < ft_strlen(str))
		i++;
	return (i);
}

int	ft_analyze_quotes(t_bash *bash)
{
	if (ft_are_there_quotes(bash->input) && !ft_check_quotes(bash))
	{
		ft_putstr_fd("quotes not closed\n", 2);
		bash->err = 2;
		return (0);
	}
	return (1);
}
