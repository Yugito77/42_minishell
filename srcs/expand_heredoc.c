/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:10:28 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/07 14:11:39 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_expand_heredoc(char *line, t_bash *bash, int quotes)
{
	int		i;
	char	*final_str;

	final_str = "";
	if (!ft_is_there_dolls(line) || quotes)
		return (line);
	else
	{
		i = 0;
		while (line[i])
		{
			final_str = ft_expand_heredoc_2(final_str, line, &i, bash);
			i++;
		}
	}
	free(line);
	return (final_str);
}

char	*ft_expand_heredoc_2(char *final_str, char *line, int *i, t_bash *bash)
{
	char	*temp2;

	temp2 = final_str;
	if (line [(*i)] == '$' && line[(*i) + 1] != '?')
		final_str = ft_expand_heredoc_3(line, i, temp2, bash);
	else if (line[(*i)] == '$' && line[(*i) + 1] == '?')
		final_str = ft_expand_heredoc_4(i, temp2, bash);
	else
		final_str = ft_strjoin_char(temp2, line[(*i)]);
	if (ft_strlen(temp2))
		free(temp2);
	return (final_str);
}

char	*ft_expand_heredoc_3(char *line, int *i, char *temp2, t_bash *bash)
{
	size_t	k;
	char	*temp;
	char	*temp3;
	char	*final_str;

	final_str = temp2;
	(*i)++;
	k = (*i);
	while ((line[k] && line[k] != '$') && ((line[k] >= 48 && line[k] <= 57)
			|| (line[k] >= 65 && line[k] <= 90)
			|| (line[k] >= 97 && line[k] <= 122) || line[k] == 95))
		k++;
	temp = ft_strndup(line, ((*i)), (k - (*i)));
	if (!ft_is_var(bash, temp))
		final_str = ft_strjoin(temp2, "");
	else
	{
		temp3 = ft_strdup(ft_is_var(bash, temp));
		final_str = ft_strjoin(temp2, temp3);
		free(temp3);
	}
	free(temp);
	(*i) = k - 1;
	return (final_str);
}

char	*ft_expand_heredoc_4(int *i, char *temp2, t_bash *bash)
{
	char	*temp;
	char	*final_str;

	final_str = temp2;
	(*i)++;
	temp = ft_itoa(bash->err);
	final_str = ft_strjoin(temp2, temp);
	free(temp);
	return (final_str);
}
