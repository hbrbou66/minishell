/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bracets_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:10 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:48:49 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_s(char *str, int *index)
{
	while (str[*index] == 32 || str[*index] == '\t')
		*index += 1;
}

int	pip_check(char *str, int *i)
{
	int	index;

	index = *i;
	if (str[*i] == '|')
	{
		index--;
		while (index >= 0 && (str[index] == 32 || str[index] == '\t'))
			index--;
		if (index == -1)
			return (e_status(2, 1), ft_syntax_error(), 1);
		if (ft_operator_count(str, *i, str[*i]) > 1)
			return (e_status(2, 1), ft_syntax_error(), 1);
		*i += 1;
		skip_s(str, i);
		if (!str[*i] || str[*i] == '|')
			return (e_status(2, 1), ft_syntax_error(), 1);
	}
	return (0);
}

int	recevied_from_input(int set, int st)
{
	static int	j;

	if (st)
		j = set;
	return (j);
}
