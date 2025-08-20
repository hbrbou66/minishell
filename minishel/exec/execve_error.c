/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:28:03 by hbou-dou          #+#    #+#             */
/*   Updated: 2025/08/19 20:31:30 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_execve_error(t_exec *head, char **envp, int err)
{
	struct stat (st);
	if (stat(head->cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(head->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		ft_malloc(0, CLEAR_DATA);
		exit(126);
	}
	if (err == ENOEXEC)
	{
		if (stat(head->cmd, &st) == 0 && st.st_size == 0)
		{
			ft_malloc(0, CLEAR_DATA);
			exit(0);
		}
		execve("/bin/sh", (char *[]){"/bin/sh", head->cmd, NULL}, envp);
	}
	perror(head->cmd);
	ft_malloc(0, CLEAR_DATA);
	if (err == ENOENT)
		exit(127);
	else if (err == EACCES)
		exit(126);
	exit(127);
}
