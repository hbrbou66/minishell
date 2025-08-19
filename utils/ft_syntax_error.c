/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:00:08 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 20:09:04 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_syntax_error(void)
{
	ft_putstr_fd("minishell : Syntax error\n", 2);
}

int	delimter(char *s, size_t index)
{
	if (index >= ft_strlen(s))
		return (0);
	while (1)
	{
		if (index > 0 && s[index] == '<' && s[index - 1] == '<')
			return (1);
		if (index == 0)
			break ;
		index--;
	}
	return (0);
}

void	init_expand(t_expand *ex)
{
	ex->index = 0;
	ex->double_q = false;
	ex->single_q = false;
	ex->start_index = 0;
}

int	check_env(char *v, t_env *e)
{
	t_expand (ex);
	init_expand(&ex);
	while (v[ex.index])
	{
		while (v[ex.index])
		{
			if (v[ex.index] == '=' && !ex.double_q && !ex.single_q)
				ex.start_index = 1;
			if (v[ex.index] == '$' && v[ex.index + 1] && check_id(v + ex.index
					+ 1) && !ex.single_q && !ex.double_q)
				break ;
			if (v[ex.index] == '\'' && !ex.double_q)
				ex.single_q = !ex.single_q;
			else if (v[ex.index] == '\"' && !ex.single_q)
				ex.double_q = !ex.double_q;
			ex.index++;
		}
		if (!v[ex.index])
			break ;
		(1) && (ex.c = get_env(v + ex.index, e), ex.index += variable_skip(v,
				ex.index));
		if (check_space(ex.c) && !ex.start_index)
			return (1);
	}
	return (0);
}
