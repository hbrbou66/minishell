/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:02 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:46:03 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_operator_count(char *str, int index, char c)
{
	int (i) = 0;
	while (str[index] == c)
	{
		i++;
		index++;
	}
	return (i);
}

void	quotes_skip(char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
}

int	check_operator(char *str, int *i)
{
	char	c;

	c = str[*i];
	if (check_redirection_pipe(str, i))
		return (2);
	if (ft_operator_count(str, *i, str[*i]) > 2)
		return (e_status(2, 1), ft_syntax_error(), 1);
	while (str[*i] == c)
		(*i)++;
	skip_s(str, i);
	if (!str[*i] || ft_strchr("|<>", str[*i]))
		return (e_status(2, 1), ft_syntax_error(), 1);
	return (0);
}

int	ft_syntax_check(char *string)
{
	int (j), (i), (count);
	j = 0;
	i = 0;
	count = 0;
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
			quotes_skip(string, &i);
		else if (string[i] && (string[i] == '<' || string[i] == '>'))
		{
			j = check_operator(string, &i);
			if (j == 2)
				continue ;
			else if (j == 1)
				return (1);
		}
		else if (string[i] && pip_check(string, &i))
			return (1);
		if (string[i])
			i++;
	}
	return (0);
}

int	ft_parse_command(char *str)
{
	if (str)
	{
		if (ft_check_quots(str))
			return (free(str), 1);
		if (ft_syntax_check(str))
			return (free(str), 1);
		if (ft_check_braces(str))
			return (free(str), 1);
	}
	return (0);
}
