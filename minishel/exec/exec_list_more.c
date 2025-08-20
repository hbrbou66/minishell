/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:23 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:46:55 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_exec *exec)
{
	int (size) = 0;
	while (exec)
	{
		size++;
		exec = exec->next;
	}
	return (size);
}

t_env	*ft_lstlast_exec(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*ft_lstnew_exec(char *key, char *value)
{
	t_env *(new) = ft_malloc(sizeof(t_env), ALLOC);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_back(t_exec **head, t_exec *new)
{
	t_exec *(tmp);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
