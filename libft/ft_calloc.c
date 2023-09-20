/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:23:14 by hcherpre          #+#    #+#             */
/*   Updated: 2021/11/25 18:26:58 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	size_alloc;
	size_t	i;
	char	*ptr;

	ptr = NULL;
	size_alloc = count * size;
	ptr = malloc(size_alloc);
	i = 0;
	if (ptr != NULL)
	{
		while (i < size_alloc)
		{
			ptr[i] = '\0';
			i++;
		}
	}
	return (ptr);
}
