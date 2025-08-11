
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
	t_var	*last;

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
	t_var	*elt;

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
	t_expand	e;
	t_var		*lst;

	(1) && (e.i = 0, e.double_q = false, e.single_q = false, lst = NULL);
	while (s[e.i])
	{
		e.b = e.i;
		while (s[e.i])
		{
			if (s[e.i] == '$' && s[e.i + 1] && id_check(s + e.i + 1) && !e.single_q)
				break ;
			if (s[e.i] == '\'' && !e.double_q)
				(1) && (e.i++, e.single_q = !e.single_q);
			else if (s[e.i] == '\"' && !e.single_q)
				(1) && (e.i++, e.double_q = !e.double_q);
			else
				e.i++;
		}
		new_var(&lst, subs(s, e.b, e.i - e.b), WORD_V);
		if (!s[e.i])
			break ;
		new_var(&lst, subs(s, e.i, skip_variable(s, e.i)), VAR);
		e.i += skip_variable(s, e.i);
	}
	return (lst);
}
