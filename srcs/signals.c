/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:36:01 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/27 16:40:21 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

void	ft_check_signal_exit(t_bash *bash)
{
	if (WIFSIGNALED(bash->err) && WTERMSIG(bash->err) == 2)
	{
		ft_putstr_fd("\n", 2);
		bash->err = 130;
	}
	else if (WIFSIGNALED(bash->err) && WTERMSIG(bash->err) == 3)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		bash->err = 131;
	}
}

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		g_bash.err = 130;
		close(g_bash.h_f);
		ft_free_all(&g_bash, false);
		ft_free_env(&g_bash);
		ft_close_int_fd();
		free(g_bash.f);
		free(g_bash.u);
		exit(g_bash.err);
	}
}

void	ctrl_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_bash.err = 130;
	}
}

void	ft_sig_quit(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_bash.err = 131;
		exit(g_bash.err);
	}
}

void	ft_handle_signals(int quit)
{
	signal(SIGINT, ctrl_handler);
	if (quit)
		signal(SIGQUIT, ft_sig_quit);
	else
		signal(SIGQUIT, SIG_IGN);
}
