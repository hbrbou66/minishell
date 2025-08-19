/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bracets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:52:43 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 19:09:46 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_len_wo_q(char *val)
{
	size_t (counter) = 0, (index) = 0, (count_inside);
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

char	*remove_q(char *val)
{
	t_expand (state);
	(1) && (state.start_index = 0, state.single_q = false, state.double_q = false,
		state.index = 0);
	if (!val)
		return (ft_strdup(""));
	state.c = ft_malloc(ft_len_wo_q(val) + 1, ALLOC);
	while (val[state.start_index])
	{
		if (val[state.start_index] == '\'' && !state.double_q)
			(1) && (state.single_q = !state.single_q, state.start_index++);
		else if (val[state.start_index] == '\"' && !state.single_q)
			(1) && (state.double_q = !state.double_q, state.start_index++);
		else if (val[state.index] == '$' && !state.double_q && !state.single_q && val[state.index
				+ 1] && ft_strchr("\'\"", val[state.index + 1]))
			state.index++;
		else if (val[state.index] == '$' && val[state.index + 1] && val[state.index + 1] == '$')
			(1) && (state.c[state.index] = val[state.start_index], state.c[state.index
				+ 1] = val[state.start_index + 1], state.start_index += 2, state.index += 2);
		else
			(1) && (state.c[state.index] = val[state.start_index], state.start_index++,
				state.index++);
	}
	state.c[state.index] = '\0';
	return (state.c);
}
