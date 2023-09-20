/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:23:20 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/06 17:52:15 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_which_doll_case(char *str, size_t *i, int qt)
{
	if ((((*i) > 0 && str[*i - 1] == DBL_QT) || \
		((*i) > 0 && str[*i - 1] == SGL_QT)) && \
		(str[*i + 1] == DBL_QT || str[*i + 1] == SGL_QT) && qt)
		return (1);
	else if ((((*i) > 0 && str[*i - 1] == DBL_QT) || \
		((*i) > 0 && str[*i - 1] == SGL_QT)) && \
		(str[*i + 1] == DBL_QT || str[*i + 1] == SGL_QT) && !qt)
		return (2);
	else if (str[*i + 1] == 32 || str[*i + 1] == '\0' \
		|| (str[*i + 1] >= 0 && str[*i + 1] < DBL_QT) \
		|| (str[*i + 1] >= 35 && str[*i + 1] < SGL_QT) \
		|| (str[*i + 1] >= 40 && str[*i + 1] < 48) \
		|| (str[*i + 1] > 57 && str[*i + 1] < 63) \
		|| (str[*i + 1] > 63 && str[*i + 1] < 65) \
		|| (str[*i + 1] > 90 && str[*i + 1] < 95) \
		|| str[*i + 1] > 122 || str[*i + 1] == 96)
		return (3);
	else if (str[*i + 1] == DBL_QT || str[*i + 1] == SGL_QT)
		return (4);
	else
		return (5);
}

char	*ft_manage_doll(char *str, size_t *i, t_bash *bash, int qt)
{
	char	*temp;
	size_t	k;

	k = 0;
	if ((*i) < ft_strlen(str))
	{
		if (ft_which_doll_case(str, i, qt) == 1)
		{
			temp = ft_strjoin_char("", str[*i]);
			return (temp);
		}
		else if (ft_which_doll_case(str, i, qt) == 2)
			return ("");
		else if (ft_which_doll_case(str, i, qt) == 3)
			return (ft_strdup("$"));
		else if (ft_which_doll_case(str, i, qt) == 4)
			return ("");
		else if (ft_which_doll_case(str, i, qt) == 5)
			return (ft_manage_doll_2(str, i, bash, k));
	}
	return (NULL);
}

char	*ft_manage_doll_2(char *str, size_t *i, t_bash *bash, size_t k)
{
	char	*temp;
	char	*final_str;

	if (str[(*i)] == '$' && str[(*i) + 1] == '?')
	{
		(*i)++;
		return (ft_itoa(bash->err));
	}
	else
	{
		(*i)++;
		k = (*i);
		while ((str[k] && str[k] != '$') && ((str[k] >= 48 && str[k] <= 57)
				|| (str[k] >= 65 && str[k] <= 90)
				|| (str[k] >= 97 && str[k] <= 122) || str[k] == 95))
			k++;
		temp = ft_strndup(str, (*i), (k - (*i)));
		(*i) = k - 1;
		if (!ft_is_var(bash, temp))
			final_str = "";
		else
			final_str = ft_strdup(ft_is_var(bash, temp));
		free(temp);
		return (final_str);
	}
}

char	*ft_is_var(t_bash *bash, char *str)
{
	t_env	*var;

	var = bash->env;
	while (var)
	{
		if (!ft_strcmp(var->key, str))
			return (var->string);
		var = var->next;
	}
	return (NULL);
}

void	ft_quotes_doll(t_bash *bash)
{
	char	*temp;
	char	*temp2;
	int		sgl;
	int		dbl;

	sgl = 0;
	dbl = 0;
	temp = ft_is_quotes(bash->input, bash, sgl, dbl);
	free(bash->input);
	temp2 = ft_strdup(temp);
	free(temp);
	bash->input = ft_strtrim(temp2, " ");
	free(temp2);
}
