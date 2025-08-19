/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraji <abrajistudent.1337>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:04 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 03:11:05 by abraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_env(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

t_exec	*new_node(void)
{
	t_exec	*ret;

	ret = ft_malloc(sizeof(t_exec), ALLOC);
	ret->fd_in = 0;
	ret->fd_out = 1;
	ret->cmd = NULL;
	ret->cmd_args = NULL;
	ret->next = NULL;
	ret->flag = 0;
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

int	ignore_first_cmd(int res, int get)
{
	static int	ret;

	if (!get)
		ret = res;
	return (ret);
}
