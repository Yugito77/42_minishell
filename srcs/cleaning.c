/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:44:30 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/27 21:31:32 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_bash_env(t_bash *bash)
{
	int	i;

	i = 0;
	while (bash->envp[i])
	{
		free(bash->envp[i]);
		i++;
	}
	free(bash->envp[i]);
	free(bash->envp);
}

void	ft_free_env(t_bash *bash)
{
	t_env	*temp;
	t_env	*next;

	if (bash->env)
	{
		temp = bash->env;
		next = temp->next;
		free(temp->key);
		free(temp);
		temp = next;
		while (temp)
		{
			next = temp->next;
			free(temp->key);
			free(temp->string);
			free(temp);
			temp = next;
		}
		bash->env = NULL;
		free(bash->env);
	}
	ft_free_bash_env(bash);
}

void	ft_free_tokens(t_token *token)
{
	t_token	*temp;
	t_token	*next;

	if (token)
	{
		temp = token;
		while (temp)
		{
			next = temp->next;
			free(temp->str);
			free(temp);
			temp = next;
		}
		token = NULL;
		free(token);
	}
}

void	ft_free_pipes(t_bash *bash)
{
	t_pipe	*temp;
	t_pipe	*next;

	if (bash->pipes)
	{
		temp = bash->pipes;
		while (temp)
		{
			next = temp->next;
			if (temp->cmd)
				free(temp->cmd);
			ft_free_split(temp->args);
			ft_free_tokens(temp->first_token);
			free(temp);
			temp = next;
		}
		bash->pipes = NULL;
		free(bash->pipes);
	}
}

void	ft_free_all(t_bash *bash, bool last)
{
	int	i;

	i = 0;
	ft_clean_err(bash);
	if (bash->exec)
	{
		while (bash->exec[i])
		{
			free(bash->exec[i]);
			i++;
		}
		free(bash->exec[i]);
		free(bash->exec);
	}
	free(bash->input);
	ft_free_tokens(bash->first_token);
	ft_free_pipes(bash);
	if (last == true)
	{
		ft_free_env(bash);
		ft_putstr_fd("exit\n", 1);
		ft_close_all_fd();
		exit(bash->err);
	}
}
