/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:04 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:38 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*new_node(void)
{
	t_exec *(ret) = ft_malloc(sizeof(t_exec), ALLOC);
	ret->fd_in = 0;
	ret->fd_out = 1;
	ret->cmd = NULL;
	ret->cmd_args = NULL;
	ret->next = NULL;
	ret->flag = 0;
	return (ret);
}

int	ft_lstsize_env(t_env *env)
{
	int (size) = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

int	ignore_first_cmd(int res, int get)
{
	static int (ret);
	if (!get)
		ret = res;
	return (ret);
}

void	ft_lstadd_back_exec(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_exec(*lst)->next = new;
}
