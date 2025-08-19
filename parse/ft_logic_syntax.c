/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:53:59 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 20:19:19 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char *str)
{
	int (indx) = 0;
	if (!str)
		return (0);
	while (str[indx])
	{
		if (ft_is_space(str[indx]))
			return (1);
		indx++;
	}
	return (0);
}
int	ft_stop_redirect(t_token *lst)
{
	t_token *(tmp) = lst;
	bool (state) = false;
	while (tmp)
	{
		if (tmp->type == WORD)
			state = true;
		tmp = tmp->next;
	}
	if (state)
		return (0);
	return (1);
}
