/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:48:42 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/05 14:11:38 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_is_quotes_5(char *s, size_t *i, t_bash *bash, int condition)
{
	if (condition)
		return (ft_manage_doll(s, i, bash, 0));
	else
		return (ft_manage_doll(s, i, bash, 1));
}

char	*ft_is_quotes_4(char *temp, char *temp2)
{
	char	*temp3;

	temp3 = ft_strjoin(temp, temp2);
	if (ft_strlen(temp2))
		free(temp2);
	return (temp3);
}

char	*ft_is_quotes_3(size_t i, char *final_str)
{
	if (!i)
		return (ft_strdup(""));
	else
		return (final_str);
}

void	ft_is_quotes_2(char s, int *sgl, int *dbl, int *sgl_first)
{
	if (s == SGL_QT)
	{
		(*sgl)++;
		if (!((*dbl) % 2) && ((*sgl) % 2))
			(*sgl_first) = 1;
		else
			(*sgl_first) = 0;
	}
	else if (s == DBL_QT)
		(*dbl)++;
}

char	*ft_is_quotes(char *s, t_bash *bash, int sgl, int dbl)
{
	size_t	i;
	int		sgl_f;
	char	*final_str;
	char	*temp;
	char	*temp2;

	sgl_f = 0;
	i = 0;
	while (s[i])
	{
		temp = ft_is_quotes_3(i, final_str);
		ft_is_quotes_2(s[i], &sgl, &dbl, &sgl_f);
		if (s[i] == '$' && (!(sgl % 2) || ((sgl % 2 && dbl % 2) && (!sgl_f))))
		{
			temp2 = ft_is_quotes_5(s, &i, bash, !(sgl % 2) && !(dbl % 2));
			final_str = ft_is_quotes_4(temp, temp2);
		}
		else
			final_str = ft_strjoin_char(temp, s[i]);
		i++;
		free(temp);
	}
	return (final_str);
}
