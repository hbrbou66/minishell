/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraji <abrajistudent.1337>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:12:11 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 03:12:34 by abraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delet_node(t_env **env, char *key)
{
	t_env	*head;
	t_env	*prev;

	if (!env || !*env)
		return ;
	head = (*env)->next;
	prev = NULL;
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
