/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:00:12 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:38:26 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	skip_tillvar(char *val, size_t i)
{
	size_t (start) = i;
	bool (single_q) = false;
	bool (double_q) = false;
	while (val[i])
	{
		if (val[i] == '\'' && !double_q)
			single_q = !single_q;
		if (val[i] == '\"' && !single_q)
			double_q = !double_q;
		if (val[i] == '$' && check_id(val + i + 1) && !single_q)
			break ;
		i++;
	}
	return (i - start);
}

int	list_size(char **list)
{
	int (size) = 0;
	if (!list)
		return (0);
	while (list[size])
		size++;
	return (size);
}

void	add_to_lst(t_token **lst, char **list, char *cmd, t_var *vars)
{
	t_split_cmd (s);
	t_token *(tmp);
	int (j), (size);
	(1) && (j = 0, s.type = WORD, size = list_size(list));
	while (list[j])
	{
		if (j == 0 && (!cmd || !cmd[0]) && list[j][0] == '\0')
			j++;
		if (!list[j])
			break ;
		if (j == 0)
			((!cmd || !cmd[0]) && (s.cmd = list[j++])) ||
			(s.cmd = strj(cmd, list[j++]));
		else if (j == size - 1 && vars->next)
			break ;
		else
			s.cmd = list[j++];
		tmp = ft_malloc(sizeof(t_token), ALLOC);
		(1) && (tmp->value = s.cmd, tmp->next = NULL);
		(1) && (tmp->previous = NULL, tmp->fd_reder = -1);
		(1) && (tmp->ambg = 0, tmp->heredoc_expn = 0, tmp->removed = 1);
		tmp->type = WORD;
		ft_lstadd_back(lst, tmp);
	}
}

static void	process_var(t_token **lst, t_var **vs_ptr, t_proc_ctx *pctx,
		char ***v_e)
{
	char **(new_v);
	char *(unq);
	int (sz);
	t_var *(vs), (tmp);
	vs = *vs_ptr;
	vs->value = get_env(vs->value, pctx->ctx->envp);
	new_v = a_split(vs->value);
	if (vs->next && vs->next->type == WORD_V)
	{
		unq = ft_remove_quotes(pctx->ctx, vs->next->value);
		sz = list_size(new_v);
		new_v[sz - 1] = strj(new_v[sz - 1], unq);
		tmp = *vs;
		tmp.next = NULL;
		add_to_lst(lst, new_v, pctx->s->cmd, &tmp);
		*vs_ptr = vs->next;
	}
	else
		add_to_lst(lst, new_v, pctx->s->cmd, vs);
	*v_e = new_v;
}

void	ft_split_expanded(char *val, t_token **lst, t_env *env)
{
	t_expand_ctx(ctx);
	t_split_cmd(s);
	t_proc_ctx(pctx);
	t_var *(vs);
	char **(v_e), **(one);
	(1) && (v_e = NULL, s.type = WORD, s.cmd = NULL, vs = s_var(val));
	(1) && (pctx.s = &s, pctx.ctx = &ctx);
	init_expan(&ctx, val, env);
	while (vs)
	{
		if (vs->type == WORD_V)
		{
			s.cmd = ft_remove_quotes(&ctx, vs->value);
			if (v_e)
				s.cmd = strj(v_e[list_size(v_e) - 1], s.cmd);
		}
		if (vs->type == VAR)
			process_var(lst, &vs, &pctx, &v_e);
		else if (vs->type == WORD_V && !vs->next)
			(1) && (one = ft_malloc(sizeof(char *) * 2, ALLOC),
				(one[0] = ft_strdup(ft_remove_quotes(&ctx, vs->value))),
				(one[1] = NULL), (add_to_lst(lst, one, s.cmd, vs), v_e = one));
		if (vs)
			vs = vs->next;
	}
}
