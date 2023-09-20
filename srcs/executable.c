/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:44:38 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/24 19:21:19 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_executable(t_bash *bash, t_pipe *pass)
{
	int	i;

	i = 0;
	if (pass->cmd)
	{
		if (pass->cmd[0] == '.' && (pass->cmd[1] == '.'
				|| pass->cmd[1] == '/'))
			i = ft_executable_2(pass, bash);
		else if (pass->cmd[0] == '/')
		{
			if (access(pass->cmd, F_OK))
			{
				ft_err_no_exec(pass->cmd, bash);
				i = 1;
			}
		}
	}
	return (i);
}

int	ft_executable_2(t_pipe *pass, t_bash *bash)
{
	char		*temp;
	DIR			*dir;
	struct stat	sb;

	temp = ft_executable_3(pass->cmd);
	dir = opendir(temp);
	if (!access(temp, F_OK) && !dir)
	{
		closedir(dir);
		if (!stat(temp, &sb) && sb.st_mode & S_IXUSR)
		{
			free(pass->cmd);
			pass->cmd = ft_strdup(temp);
			return (free(temp), 0);
		}
	}
	else
	{
		closedir(dir);
		ft_err_no_exec(pass->cmd, bash);
	}
	return (free(temp), 1);
}

char	*ft_executable_3(char *cmd)
{
	int		i;
	char	*cwd;
	char	*temp;
	char	*new;
	char	buf[MAX_LINE_LEN];

	i = 0;
	cwd = getcwd(buf, MAX_LINE_LEN);
	while (cmd[i] != '/')
		i++;
	new = ft_strndup(cmd, i, ft_strlen(cmd) - 1);
	if (i == 2)
	{
		temp = ft_delete_dir(cwd);
		cwd = ft_strjoin(temp, new);
		free (temp);
	}
	else
		cwd = ft_strjoin(cwd, new);
	free(new);
	return (cwd);
}

char	*ft_delete_dir(char *cwd)
{
	int		i;
	int		j;
	char	*new_cwd;

	i = 0;
	i = ft_strlen(cwd);
	while (cwd[i] != '/')
		i--;
	i--;
	new_cwd = ft_calloc(ft_strlen(cwd) - ft_strlen(cwd) + i + 2, sizeof(char));
	if (!new_cwd)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		new_cwd[j] = cwd[j];
		j++;
	}
	return (new_cwd);
}
