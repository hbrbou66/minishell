/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:30 by abraji            #+#    #+#             */
/*   Updated: 2025/08/20 00:40:54 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_exit(char *opt)
{
	if (!opt)
		return (1);
	if (ft_strlen(opt) == 0)
		return (1);
	if (*opt == '-' || *opt == '+')
		opt++;
	while (*opt >= '0' && *opt <= '9')
		opt++;
	if (*opt && !(*opt >= '0' && *opt <= '9'))
		return (1);
	return (0);
}

int	e_status(int sts, int set)
{
	static int (status);
	if (set)
		status = sts;
	return (status);
}

void	ambiguous_red(void)
{
	ft_putstr_fd("minishell : ambiguous redirect\n", 2);
}

void	err_num(char *opt)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(opt, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(2);
}

int	ft_exec_exit(char **opt, bool forked)
{
	int (nbr) = 0;
	int (flag) = 0;
	if (forked == false)
		ft_putstr_fd("exit\n", 1);
	if (opt[0] && !opt[1])
	{
		ft_malloc(0, CLEAR_DATA);
		exit(e_status(0, 0));
	}
	else if (is_valid_exit(opt[1]))
		err_num(opt[1]);
	else if (opt[1] && !is_valid_exit(opt[1]) && !opt[2])
	{
		nbr = ft_atoi(opt[1], &flag);
		if (flag == 1)
			err_num(opt[1]);
		ft_malloc(0, CLEAR_DATA);
		exit(nbr);
	}
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (ft_malloc(0, CLEAR_DATA), e_status(1, 1));
	}
	return (0);
}
