/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:49:49 by hcherpre          #+#    #+#             */
/*   Updated: 2021/11/23 15:37:53 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *pointer, size_t n)
{
	unsigned int	i;
	unsigned char	*save_p;

	save_p = (unsigned char *) pointer;
	i = 0;
	while (i < n)
	{
		save_p[i] = '\0';
		i++;
	}
}
