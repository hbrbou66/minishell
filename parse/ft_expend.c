
#include "../minishell.h"

int	id_check(char *var)
{
	int	i;

	i = 0;
	if (!(ft_isalnum(var[i]) || var[i] == '?' \
	|| var[i] == '_' || var[i] == '$'))
		return (0);
	i++;
	while (var[i])
	{
		if (!(ft_isalnum(var[i]) || var[i] == '?' \
		|| var[i] == '_'))
			return (i);
		i++;
	}
	return (i);
}

int	skip_variable(char *value, int index)
{
	int	count;

	count = index + 1;
	if (value[count] == '$' || value[count] == '?' \
		|| (value[count] >= '0' && value[count] <= '9'))
	{
		return (2);
	}
	count += id_check(value + count);
	return (count - index);
}

size_t	ft_len_wo_quotes(t_expand_ctx *c, char *value)
{
	size_t	count;
	size_t	i;
	bool	double_q;
	bool	single_q;

	(1) && (i = 0, count = 0, double_q = c->e.double_q, single_q = c->e.single_q);
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '\'' && !double_q)
		{
			single_q = !single_q;
			i++;
		}
		else if (value[i] == '\"' && !single_q)
		{
			double_q = !double_q;
			i++;
		}
		else
			(1) && (count++, i++);
	}
	return (count);
}

char	*ft_remove_quotes(t_expand_ctx *c, char *tmp)
{
	int		index;
	char	*clean;
	int		index_tmp;

	index = 0;
	index_tmp = 0;
	if (!tmp)
		return (ft_strdup(""));
	clean = ft_malloc(ft_len_wo_quotes(c, tmp) + 1, ALLOC);
	while (tmp[index_tmp])
	{
		if (tmp[index_tmp] == '\'' && !c->e.double_q)
			(1) && (c->e.single_q = !c->e.single_q, index_tmp++);
		else if (tmp[index_tmp] == '\"' && !c->e.single_q)
			(1) && (c->e.double_q = !c->e.double_q, index_tmp++);
		else if (tmp[index_tmp] == '$' && !c->e.double_q \
			&& !c->e.single_q && ft_strchr("\'\"", tmp[index + 1]))
			index_tmp++;
		else
			(1) && (clean[index] = tmp[index_tmp], index_tmp++, index++);
	}
	clean[index] = '\0';
	return (clean);
}

int	ft_expand(t_token *lst, t_env *envp)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (check_type_exp(tmp->type))
			tmp->type = WORD;
		if (tmp->type == HERDOC)
		{
			tmp->fd_reder = handle_heredoc(tmp, envp);
			if (tmp->fd_reder == -1)
				continue ;
			else if (tmp->fd_reder == -2)
				return (1);
		}
		if (!tmp->removed)
			tmp->value = remove_q(tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
