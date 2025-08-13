
#include "../minishell.h"

int	ft_stop_redirect(t_token *lst, t_env *envp)
{
	t_token	*tmp;
	bool	f;

	tmp = lst;
	f = false;
	while (tmp)
	{
		if (tmp->type == WORD)
			f = true;
		tmp = tmp->next;
	}
	(void)envp;
	if (f)
		return (0);
	return (1);
}

bool	check_assi(char *st, int index)
{
	int	i;

	i = index;
	while (st[index] && !ft_is_space(st[index]))
	{
		if (ft_strchr("+-=", st[index]))
			return (1);
		index++;
	}
	while (i >= 0 && !ft_is_space(st[i]))
	{
		if (ft_strchr("+-=", st[i]))
			return (1);
		i--;
	}
	return (false);
}

bool	should_expand(char *s, t_expand e)
{
	return ((s[e.index] == '$' && !e.single_q && s[e.index + 1] \
	&& !delimter(s, e.index)));
}

bool	is_invalid_dollar_after_op(t_expand_ctx *c)
{
	if (c->source_string[c->expand_state.index] == '$' && c->source_string[c->expand_state.index + 1] == '"' \
		&& c->expand_state.double_q)
		return (true);
	return ((c->source_string[c->expand_state.index] == '$' && check_assi(c->source_string, c->expand_state.index)));
}

int	check_for_s(char *string)
{
	int	indx;

	indx = 0;
	if (!string)
		return (0);
	while (string[indx])
	{
		if (ft_is_space(string[indx]))
			return (1);
		indx++;
	}
	return (0);
}
