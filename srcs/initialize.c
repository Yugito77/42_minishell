/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:33:55 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/26 19:18:09 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_new_env(t_bash *bash, char *key, char *string)
{
	t_env	*last;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	last = bash->env;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
	new->key = key;
	new->string = string;
}

void	ft_create_first_env(t_bash *bash)
{
	bash->env = ft_calloc(1, sizeof(t_env));
	if (!bash->env)
		return ;
	bash->env->key = ft_strdup(" === BEG OF ENV === ");
	bash->env->string = NULL;
	bash->env->next = NULL;
}

void	ft_get_env(t_bash *bash, char **envp)
{
	int		i;
	int		j;
	char	*key;
	char	*string;
	char	**temp;

	i = 0;
	temp = NULL;
	string = NULL;
	ft_create_first_env(bash);
	while (envp[i])
	{
		j = 0;
		temp = ft_split(envp[i], "=");
		key = ft_strdup(temp[0]);
		string = ft_substr(envp[i], ft_strlen(temp[0]) + 1,
				ft_strlen(envp[i]) - ft_strlen(temp[0]) - 1);
		ft_new_env(bash, key, string);
		while (temp[j])
			free(temp[j++]);
		free(temp[j]);
		free(temp);
		i++;
	}
}

void	ft_cpy_env(t_bash *bash, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	bash->envp = ft_calloc(i + 1, sizeof(char *));
	if (!bash->envp)
		return ;
	i = 0;
	while (envp[i])
	{
		bash->envp[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	ft_initialize_bash(t_bash *bash, char **envp, bool first)
{
	bash->input = NULL;
	if (first == true)
		bash->env = NULL;
	bash->exec = NULL;
	bash->first_token = NULL;
	bash->pipes = NULL;
	ft_create_first_pipe(bash);
	ft_create_first_token(bash);
	if (first == true)
	{
		ft_cpy_env(bash, envp);
		ft_get_env(bash, envp);
	}
	ft_get_exec(bash);
}
