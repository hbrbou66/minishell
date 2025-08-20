/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:12:11 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:35 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delet_node(t_env **env, char *key)
{
	t_env *(head);
	t_env *(prev) = NULL;
	if (!env || !*env)
		return ;
	head = (*env)->next;
	if (!*env)
		return ;
	if (!ft_strcmp((*env)->key, key))
	{
		*env = (*env)->next;
		return ;
	}
	prev = *env;
	while (head)
	{
		if (!ft_strcmp(head->key, key))
		{
			prev->next = head->next;
			return ;
		}
		prev = head;
		head = head->next;
	}
}

void	ft_unset(char **opt, t_env **env)
{
	while (*opt)
	{
		delet_node(env, *opt);
		opt++;
	}
}
