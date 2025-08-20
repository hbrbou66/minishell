/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:04:34 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 23:03:49 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_memory	*ft_lstlast_memory(t_memory *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_to_memory(t_memory **lst, t_memory *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_memory(*lst)->next = new;
}

t_memory	*ft_new_memory(void *adress)
{
	t_memory	*new;

	new = malloc(sizeof(t_memory));
	if (!new)
	{
		free(adress);
		perror("malloc()");
		ft_malloc(0, CLEAR_DATA);
		return (NULL);
	}
	new->address = adress;
	new->next = NULL;
	return (new);
}

void	clear_it(t_memory *memory)
{
	t_memory	*clear;

	while (memory)
	{
		clear = memory->next;
		free(memory->address);
		free(memory);
		memory = clear;
	}
}

void	*ft_malloc(size_t size, int flag)
{
	static t_memory	*memory;
	void			*ret;

	if (flag == CLEAR_DATA)
	{
		clear_it(memory);
		return (NULL);
	}
	ret = ft_calloc(size, 1);
	if (!ret)
	{
		clear_it(memory);
		perror("malloc()");
		exit(1);
	}
	add_to_memory(&memory, ft_new_memory(ret));
	return (ret);
}
