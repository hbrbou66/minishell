/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:13 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 21:10:30 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_var_check(char *str)
{
	int (i) = 0, (single_q) = 0, (double_q) = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		if (str[i] == '\"' && !single_q)
			double_q = !double_q;
		if (str[i] == '$' && str[i + 1] && check_id(str + i + 1)
			&& !single_q)
			return (1);
		i++;
	}
	return (0);
}

int	heredoc_count(t_token *lst)
{
	t_token *(tmp);
	int (count) = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->type == HERDOC)
			count++;
		tmp = tmp->next;
	}
	if (count >= 16)
	{
		ft_putstr_fd("minishell : maximum here-document count exceeded\n", 2);
		return (e_status(2, 1), 1);
	}
	return (0);
}

t_tokentype	ft_token_type(t_token *lst, char *str)
{
	t_token	*last;

	last = ft_lstlast(lst);
	if (last && (last->type == R_IN || last->type == R_OUT
			|| last->type == APPEND))
		return (RED_FILE);
	if (!str)
		return (WORD);
	if (ft_var_check(str))
		return (EXPAN);
	if (ft_pip_check(str))
		return (PIPE);
	if (ft_redirect_in(str))
		return (R_IN);
	if (ft_redirect_out(str))
		return (R_OUT);
	if (ft_append(str))
		return (APPEND);
	if (ft_heredoc(str))
		return (HERDOC);
	if (ft_quotes_type(str) == SINGLE)
		return (SINGLE_Q);
	if (ft_quotes_type(str) == DOUBLE)
		return (DOUBLE_Q);
	return (WORD);
}

t_token	*s_cmd(char **cmd, t_env *envp)
{
	t_token *(lst)	= NULL;
	int (i) = 0;
	t_split_cmd (s);
	if (!cmd || !*cmd)
		return (NULL);
	while (cmd[i])
	{
		s.cmd = cmd[i];
		s.type = ft_token_type(lst, cmd[i]);
		ft_lstnew(&lst, s, envp, 0);
		i++;
	}
	if (heredoc_count(lst))
		return (NULL);
	return (lst);
}
