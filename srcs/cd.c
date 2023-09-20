/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:02:47 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/11 18:30:23 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd_msg_err(char *str, t_bash *bash)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin("minishell: cd: ", str);
	temp2 = ft_strjoin(temp, ": No such file or directory\n");
	free(temp);
	ft_putstr_fd(temp2, 2);
	free(temp2);
	bash->err = 1;
}

void	ft_update_old_pwd(t_bash *bash, char *old)
{
	t_env	*env;
	char	*temp;
	int		i;

	if (old)
	{
		env = bash->env;
		while (env && ft_strcmp(env->key, "OLDPWD"))
			env = env->next;
		if (env)
		{
			free(env->string);
			env->string = ft_strdup(old);
		}
		i = 0;
		while (bash->envp[i] && ft_strncmp(bash->envp[i], "OLDPWD=", 7))
			i++;
		if (bash->envp[i])
		{
			free(bash->envp[i]);
			temp = ft_strjoin("OLDPWD=", old);
			bash->envp[i] = ft_strdup(temp);
			free(temp);
		}
	}
}

void	ft_update_pwd(t_bash *bash, char *old, char buf[MAX_LINE_LEN])
{
	int		i;
	char	*temp;
	char	*new;
	t_env	*env;

	env = bash->env;
	new = getcwd(buf, MAX_LINE_LEN);
	while (env && ft_strcmp(env->key, "PWD"))
		env = env->next;
	if (env)
	{
		free(env->string);
		env->string = ft_strdup(new);
	}
	i = 0 ;
	while (bash->envp[i] && ft_strncmp(bash->envp[i], "PWD=", 4))
		i++;
	if (bash->envp[i])
	{
		free(bash->envp[i]);
		temp = ft_strjoin("PWD=", new);
		bash->envp[i] = ft_strdup(temp);
		free(temp);
	}
	ft_update_old_pwd(bash, old);
}

int	ft_check_cd_args(t_token *token, t_bash *bash)
{
	if (!token->next || (token->next && token->next->type != T_STR))
		return (1);
	if (token->next && token->next->type == T_STR && token->next->next
		&& token->next->next->type == T_STR)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		bash->err = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_pipe *pipe, t_bash *bash, char *old, char buf[MAX_LINE_LEN])
{
	int		c;
	char	*new;
	t_token	*token;
	char	*temp;

	token = pipe->first_token;
	while (token->type != T_CMD)
		token = token->next;
	if (ft_check_cd_args(token, bash))
		return ;
	if (old)
		temp = ft_strdup(old);
	else
		temp = NULL;
	token = token->next;
	new = getcwd(buf, MAX_LINE_LEN);
	c = chdir(token->str);
	if (c == -1 || (!new))
		ft_cd_msg_err(token->str, bash);
	else
		ft_update_pwd(bash, temp, buf);
	free(temp);
}
