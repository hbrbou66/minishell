/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bracets_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:52:43 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:42:52 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_len_wo_q(char *val)
{
	size_t (counter) = 0;
	size_t (index) = 0;
	size_t (count_inside);
	char (c);
	if (!val)
		return (0);
	while (val[index])
	{
		if (val[index] == '\'' || val[index] == '\"')
		{
			c = val[index];
			count_inside = 0;
			index++;
			while (val[index] && val[index] != c)
				(1) && (count_inside++, index++);
			if (val[index] == c)
				index++;
			counter += count_inside;
		}
		else
			(1) && (counter++, index++);
	}
	return (counter);
}

int	check_end(char *str, char c, int *index)
{
	while (str[*index] && str[*index] != c)
		(*index)++;
	if (!str[*index])
	{
		e_status(2, 1);
		ft_syntax_error();
		return (1);
	}
	return (0);
}

int	check_redirection_pipe(char *str, int *index)
{
	if (str[*index] == '>' && str[*index + 1] && str[*index + 1] == '|')
	{
		(*index) += 1;
		return (1);
	}
	return (0);
}

int	ft_check_braces(char *str)
{
	int (index) = 0;
	while (str[index])
	{
		if (str[index] == '{')
		{
			if (check_end(str, '}', &index))
				return (1);
			index++;
		}
		else if (str[index] == '}')
			return (e_status(2, 1), ft_syntax_error(), 1);
		else
			index++;
	}
	return (0);
}

char	*remove_q(char *v)
{
	t_expand (s);
	(1) && (s.start_index = 0, s.single_q = false,
		s.double_q = false, s.index = 0);
	if (!v)
		return (ft_strdup(""));
	s.c = ft_malloc(ft_len_wo_q(v) + 1, ALLOC);
	while (v[s.start_index])
	{
		if (v[s.start_index] == '\'' && !s.double_q)
			(1) && (s.single_q = !s.single_q, s.start_index++);
		else if (v[s.start_index] == '\"' && !s.single_q)
			(1) && (s.double_q = !s.double_q, s.start_index++);
		else if (v[s.index] == '$' && !s.double_q && !s.single_q
			&& v[s.index + 1] && ft_strchr("\'\"", v[s.index + 1]))
			s.index++;
		else if (v[s.index] == '$' && v[s.index + 1] && v[s.index + 1] == '$')
			(1) && (s.c[s.index] = v[s.start_index], s.c[s.index
				+ 1] = v[s.start_index + 1], s.start_index += 2, s.index += 2);
		else
			(1) && (s.c[s.index] = v[s.start_index], s.start_index++,
				s.index++);
	}
	s.c[s.index] = '\0';
	return (s.c);
}
