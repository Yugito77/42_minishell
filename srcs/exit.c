/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:53:41 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/27 15:14:31 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

unsigned long long int	ft_long_atoi(const char *str)
{
	int						i;
	int						neg;
	unsigned long long int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	(void) neg;
	return (nb);
}

int	ft_check_min_long(char *s)
{
	int		i;
	char	*min;
	char	*str;
	bool	neg;

	i = 0;
	if (s[0] != '-')
		neg = false;
	else
	{
		neg = true;
		i++;
	}
	while (s[i] && s[i] == '0')
		i++;
	str = ft_strndup(s, i, ft_strlen(s) - i);
	if (ft_strlen(str) > 19)
		return (free(str), 2);
	min = ft_strdup("9223372036854775808");
	if (!ft_strcmp(min, str) && neg)
		return (free(str), free(min), 1);
	return (free(str), free(min), 0);
}

int	ft_is_str_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
		i++;
	}
	if (ft_check_min_long(s) == 2)
		return (0);
	if (ft_check_min_long(s))
		return (1);
	if (ft_long_atoi(s) > 9223372036854775807)
		return (0);
	return (1);
}

int	ft_are_args_num(t_pipe *pipe)
{
	int	i;

	i = 0;
	while (pipe->args[i])
	{
		if (!ft_is_str_num(pipe->args[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_pipe *pipe)
{
	if (pipe->args)
	{
		if (pipe->args[1] && ft_is_str_num(pipe->args[0]))
		{
			ft_putstr_fd("minishell: exit\ntoo many arguments\n", 2);
			g_bash.err = 1;
			return ;
		}
		if (pipe->args[0] && !ft_are_args_num(pipe))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(pipe->args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_bash.err = 2;
			ft_free_all(&g_bash, true);
		}
		if (pipe->args[0][0] == '-')
			g_bash.err = -ft_long_atoi(pipe->args[0]);
		else
			g_bash.err = ft_long_atoi(pipe->args[0]);
		ft_free_all(&g_bash, true);
	}
	ft_free_all(&g_bash, true);
}
