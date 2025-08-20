/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:59:38 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:13:39 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_split_ex(t_token **lst, t_env *e, char *value, t_tokentype type)
{
	t_token *(elt) = NULL;
	char *(exp);
	int (f) = check_env(value, e);
	if (!f || (f && type == RED_FILE))
	{
		exp = exp_val(value, e);
		elt = ft_malloc(sizeof(t_token), ALLOC);
		elt->type = type;
		(1) && (elt->value = exp, elt->next = NULL, elt->previous = NULL);
		elt->removed = 1;
		if (type == RED_FILE)
		{
			if (!exp || !exp[0] || f)
				elt->ambg = 1;
		}
		else
			elt->ambg = 0;
		if (type == RED_FILE)
			type = WORD;
		return (ft_lstadd_back(lst, elt));
	}
	else
		ft_split_expanded(value, lst, e);
}

void	ft_lstnew(t_token **lst, t_split_cmd s, t_env *e, int r)
{
	t_token *(elt) = ft_malloc(sizeof(t_token), ALLOC);
	t_token *(last) = ft_lstlast(*lst);
	elt->value = s.cmd;
	elt->next = NULL;
	elt->previous = NULL;
	elt->fd_reder = -1;
	elt->ambg = 0;
	elt->heredoc_expn = 0;
	elt->removed = r;
	if (last && last->type == HERDOC)
		s.type = DELEMTER;
	if (ft_var_check(s.cmd) && s.type != DELEMTER)
		return (ft_split_ex(lst, e, s.cmd, s.type));
	if (s.type == DELEMTER && (ft_strchr(s.cmd, '\'') \
	|| ft_strchr(s.cmd, '\"')))
	{
		elt->value = remove_q(s.cmd);
		elt->heredoc_expn = 1;
	}
	elt->type = s.type;
	ft_lstadd_back(lst, elt);
}

int	shouldnt_split(char *v, t_tokentype type, int f)
{
	int (i) = 0;
	bool (double_q) = false;
	bool (single_q) = false;
	int (operator) = 0;
	if (type == RED_FILE)
		return (1);
	while (v[i])
	{
		if (v[i] == '\'' && !double_q)
			single_q = !single_q;
		if (v[i] == '\"' && !single_q)
			double_q = !double_q;
		if (v[i] == '$' && v[i + 1] && check_id(v + 1 + i) && operator && f)
			return (1);
		if (v[i] == '=' && !double_q)
			operator = 1;
		i++;
	}
	return (0);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token *(tmp);
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->previous = tmp;
}
