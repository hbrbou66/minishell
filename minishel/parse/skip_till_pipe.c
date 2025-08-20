/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_till_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:18 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 22:02:41 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_till_pipe(t_token **lst)
{
	if (!lst)
		return ;
	while ((*lst)->next && (*lst)->next->type != PIPE)
		(*lst) = (*lst)->next;
}

int	handl_norm_redirects(t_token **lst, t_exec *node, int status)
{
	if ((*lst)->type == HERDOC)
	{
		if ((*lst)->fd_reder == -1)
			status = 1;
		else
		{
			if (node->fd_in != -1)
				close(node->fd_in);
			node->fd_in = (*lst)->fd_reder;
		}
	}
	else if ((*lst)->type == R_IN)
		status = handle_red_in(lst, node);
	else if ((*lst)->type == APPEND)
		status = handle_append(lst, node);
	else if ((*lst)->type == R_OUT)
	{
		status = handle_red_out(lst, node);
		if (status && status != 33)
			e_status(1, 2);
	}
	if (status && status != 33)
		e_status(1, 1);
	return (status);
}

int	handle_redirects(t_token **lst, t_exec *node)
{
	int (status);
	status = 0;
	status = handl_norm_redirects(lst, node, status);
	return (status);
}
