/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quots_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:52:53 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:43:36 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_unclosed_quote(void)
{
	ft_putstr_fd("minishell: quotes not closed\n", 2);
}

int	ft_check_end(char *cmd, char c)
{
	int (i) = 1;
	while (cmd[i] && cmd[i] != c)
		i++;
	if (cmd[i] == c)
		return (i);
	ft_unclosed_quote();
	return (-1);
}

int	ft_check_quots(char *cmd)
{
	int (i) = 0;
	int (result) = -1;
	char (c);
	while (cmd[i])
	{
		if (ft_strchr("\'\"", cmd[i]))
		{
			c = cmd[i];
			result = ft_check_end(cmd + i, c);
			if (result == -1)
				return (e_status(2, 1), 1);
			i += result;
		}
		i++;
	}
	return (0);
}
