/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:10:54 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:07 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_option(char *str)
{
	int (i) = 1;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(char **cmd, int fd)
{
	int (n_line) = 0;
	int (i) = 1;
	while (cmd[i] && is_valid_option(cmd[i]))
	{
		n_line = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!n_line)
		write(fd, "\n", 1);
	e_status(0, 1);
	return (0);
}
