/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:08 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 22:02:42 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_execve(t_exec *head, t_env *env)
{
	char	**envp;
	int		err;

	envp = convert_t_env(env);
	execve(head->cmd, head->cmd_args, envp);
	err = errno;
	handle_execve_error(head, envp, err);
}

void	in_child(t_exec *head, t_env **env, int *fd)
{
	if (head->flag)
	{
		close(fd[0]);
		close(fd[1]);
		ft_malloc(0, CLEAR_DATA);
		exit(1);
	}
	if (is_builtin(head->cmd))
	{
		setup_child(fd, NULL, head, 1);
		execute_builtin(head, env, true);
		exit(0);
	}
	else
	{
		setup_child(fd, find_env(*env, "PATH"), head, 0);
		call_execve(head, *env);
	}
}

pid_t	execute_cmd(t_exec *head, t_env **env)
{
	int (fd)[2];
	pid_t (pid);
	if (pipe(fd) == -1)
		return (perror("pipe"), ft_malloc(0, CLEAR_DATA), -1);
	child_signal(head->cmd);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), perror("fork"), ft_malloc(0,
				CLEAR_DATA), -1);
	if (pid == 0)
	{
		default_signal();
		in_child(head, env, fd);
	}
	else
		parent_thing(fd, head);
	return (pid);
}

static pid_t	exec_loop(t_exec *exec, t_env **env, int *had_error)
{
	pid_t (last_pid) = -1;
	while (exec)
	{
		if (exec->flag)
			*had_error = 1;
		last_pid = execute_cmd(exec, env);
		if (exec->fd_in > 0)
			close(exec->fd_in);
		if (exec->fd_out > 2)
			close(exec->fd_out);
		exec = exec->next;
	}
	return (last_pid);
}

int	execution(t_exec *exec, t_env **env)
{
	int (fd), (had_error) = 0, (code);
	pid_t (last_pid);
	if (ft_lstsize(exec) == 1 && is_builtin(exec->cmd))
		return (execute_builtin(exec, env, false), 1);
	fd = dup(STDIN_FILENO);
	if (fd == -1)
	{
		perror("dup()");
		ft_malloc(0, CLEAR_DATA);
		return (1);
	}
	last_pid = exec_loop(exec, env, &had_error);
	dup2(fd, 0);
	close(fd);
	if (last_pid == -1)
	{
		if (had_error)
			return (e_status(1, 1));
		else
			return (e_status(0, 0));
	}
	code = check_exit_status(last_pid);
	if (had_error && code == 128 + SIGPIPE)
		return (e_status(1, 1));
	return (code);
}
