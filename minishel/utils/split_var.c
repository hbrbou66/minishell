/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:00:15 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:28:03 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*last_var(t_var *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_var_back(t_var **lst, t_var *elt)
{
	t_var *(last);
	if (!elt)
		return ;
	if (!*lst)
	{
		*lst = elt;
		return ;
	}
	last = last_var(*lst);
	last->next = elt;
}

void	new_var(t_var **lst, char *value, t_vartype type)
{
	t_var *(elt);
	if (value)
	{
		elt = ft_malloc(sizeof(t_var), ALLOC);
		elt->next = NULL;
		elt->type = type;
		elt->value = value;
		add_var_back(lst, elt);
	}
}

t_var	*s_var(char *s)
{
	t_expand (e);
	t_var *(lst);
	(1) && (e.index = 0, e.double_q = false, e.single_q = false, lst = NULL);
	while (s[e.index])
	{
		e.start_index = e.index;
		while (s[e.index])
		{
			if (s[e.index] == '$' && s[e.index + 1] && check_id(s + e.index + 1)
				&& !e.single_q)
				break ;
			if (s[e.index] == '\'' && !e.double_q)
				(1) && (e.index++, e.single_q = !e.single_q);
			else if (s[e.index] == '\"' && !e.single_q)
				(1) && (e.index++, e.double_q = !e.double_q);
			else
				e.index++;
		}
		new_var(&lst, subs(s, e.start_index, e.index - e.start_index), WORD_V);
		if (!s[e.index])
			break ;
		new_var(&lst, subs(s, e.index, variable_skip(s, e.index)), VAR);
		e.index += variable_skip(s, e.index);
	}
	return (lst);
}
