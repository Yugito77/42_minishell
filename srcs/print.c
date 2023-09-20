/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:50:45 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/15 13:30:45 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tokens(t_bash *bash)
{
	t_token	*print;

	print = ft_first_token(bash->first_token);
	while (print)
	{
		printf("TOKEN: %s TOKEN TYPE: %c\n", print->str, print->type);
		print = print->next;
	}
}

void	ft_print_env(t_bash *bash, char *key)
{
	t_env	*print;

	print = bash->env;
	while (ft_strcmp(print->key, key))
		print = print->next;
	if (print)
	{
		printf("%s ", key);
		printf("%s\n", print->string);
	}
}

void	ft_print_pipes(t_bash *bash)
{
	t_pipe	*pipe;
	t_token	*print;

	pipe = bash->pipes;
	while (pipe)
	{
		printf("NEW PIPE\n");
		print = pipe->first_token;
		while (print)
		{
			printf("%s / TYPE: %c\n", print->str, print->type);
			print = print->next;
		}
		pipe = pipe->next;
	}
}

void	ft_print_envp(t_bash *bash, char *key)
{
	int	i;

	i = 0;
	while (ft_strncmp(bash->envp[i], key, ft_strlen(key)))
		i++;
	printf("envp: %s\n", bash->envp[i]);
}
