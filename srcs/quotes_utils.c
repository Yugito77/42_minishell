/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoo <hugoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:38 by hcherpre          #+#    #+#             */
/*   Updated: 2022/06/15 14:04:01 by hugoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_quotes(char *str)
{
	size_t	i;
	size_t	j;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == SGL_QT || str[i] == DBL_QT)
		{
			j = i;
			i++;
			while (str[i] != str[j])
				i++;
			i++;
			count += 2;
		}
		else
			i++;
	}
	return (count);
}

size_t	ft_index_closing_quote(char *str, size_t i)
{
	i++;
	if (str[i - 1] == SGL_QT)
	{
		while (str[i] != SGL_QT)
			i++;
	}
	else
	{
		while (str[i] != DBL_QT)
			i++;
	}
	return (i);
}
