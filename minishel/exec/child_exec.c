/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:01 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 21:03:06 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_not_found(char *cmd)
{
	if (!cmd)
		exit(0);
	write(2, cmd, ft_strlen(cmd));
	ft_putstr_fd(": command not found\n", 2);
	ft_malloc(0, CLEAR_DATA);
	exit(127);
}

int	check_exit_status(pid_t last_pid)
{
	int (status);
	int (exit_code) = 0;
	pid_t (pid) = wait(&status);
	while (pid != -1)
	{
		if (pid == last_pid)
		{
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)", 19);
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				write(1, "\n", 1);
				exit_code = 128 + WTERMSIG(status);
			}
		}
		pid = wait(&status);
	}
	e_status(exit_code, 1);
	return (exit_code);
}

static void	redirect_fds(int *fd, t_exec *head)
{
	if (head->fd_in != STDIN_FILENO && head->fd_in > 0)
	{
		dup2(head->fd_in, STDIN_FILENO);
		close(head->fd_in);
	}
	if (head->fd_out != STDOUT_FILENO && head->fd_out >= 0)
	{
		dup2(head->fd_out, STDOUT_FILENO);
		close(head->fd_out);
	}
	else if (head->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
}

int	parent_thing(int *fd, t_exec *head)
{
	if (head->next && dup2(fd[0], 0) == -1)
		perror("dup2");
	close(fd[0]);
	close(fd[1]);
	return (1);
}

void	setup_child(int *fd, t_env *path, t_exec *head, int bltn)
{
	char *(pth);
	if (!bltn)
	{
		pth = NULL;
		if (path)
			pth = path->value;
		if (!ft_strchr(head->cmd, '/'))
			head->cmd = get_cmd_path(head->cmd, pth);
	}
	if (bltn)
	{
		if (head->fd_out == STDOUT_FILENO && head->next)
			head->fd_out = fd[1];
		close(fd[0]);
		return ;
	}
	redirect_fds(fd, head);
}
