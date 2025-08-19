/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:04 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 20:21:09 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quotes_type(char *str)
{
	int (index) = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			return (SINGLE);
		if (str[index] == '\"')
			return (DOUBLE);
		index++;
	}
	return (0);
}
