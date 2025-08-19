/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:53:54 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 19:40:40 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_len_no_q(t_expand_ctx *ctx, char *val)
{
	size_t (count) = 0, (index) = 0;
	bool (double_q), (single_q);
	double_q = ctx->expand_state.double_q;
	single_q = ctx->expand_state.single_q;
	if (!val)
		return (0);
	while (val[index])
	{
		if (val[index] == '\'' && !double_q)
		{
			single_q = !single_q;
			index++;
		}
		else if (val[index] == '\"' && !single_q)
		{
			double_q = !double_q;
			index++;
		}
		else
			{
				count++;
				index++;
			}
	}
	return (count);
}

int	ft_expand(t_token *lst, t_env *env)
{
	t_token *(tmp);
	tmp = lst;
	while (tmp)
	{
		if (check_exp_type(tmp->type))
			tmp->type = WORD;
		if (tmp->type == HERDOC)
		{
			tmp->fd_reder = handle_heredoc(tmp, env);
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

char	*ft_remove_quotes(t_expand_ctx *ctx, char *tmp)
{
	int (index) = 0, (tmp_index) = 0;
	char *(clean);
	if (!tmp)
		return (ft_strdup(""));
	clean = ft_malloc(ft_len_no_q(ctx, tmp) + 1, ALLOC);
	while (tmp[tmp_index])
	{
		if (tmp[tmp_index] == '\'' && !ctx->expand_state.double_q)
			{
				ctx->expand_state.single_q = !ctx->expand_state.single_q;
				tmp_index++;
			}
		else if (tmp[tmp_index] == '\"' && !ctx->expand_state.single_q)
			{
				ctx->expand_state.double_q = !ctx->expand_state.double_q;
				tmp_index++;
			}
		else if (tmp[tmp_index] == '$' && !ctx->expand_state.double_q
			&& !ctx->expand_state.single_q && ft_strchr("\'\"", tmp[tmp_index + 1]))
			tmp_index++;
		else
			(1) && (clean[index] = tmp[tmp_index], tmp_index++, index++);
	}
	clean[index] = '\0';
	return (clean);
}

int	check_id(char *var)
{
	int (index) = 0;
	if (!(ft_isalnum(var[index]) || var[index] == '?' || var[index] == '_'
			|| var[index] == '$'))
		return (0);
	index++;
	while (var[index])
	{
		if (!(ft_isalnum(var[index]) || var[index] == '?' || var[index] == '_'))
			return (index);
		index++;
	}
	return (index);
}

int	variable_skip(char *val, int index)
{
	int (count);
	count = index + 1;
	if (val[count] == '$' || val[count] == '?' || (val[count] >= '0'
			&& val[count] <= '9'))
		return (2);
	count += check_id(val + count);
	return (count - index);
}
