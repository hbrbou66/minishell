/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:15 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 21:11:11 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_append(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (true);
	return (false);
}

bool	ft_redirect_out(char *str)
{
	if (str[0] == '>' && str[1] != '>')
		return (true);
	return (false);
}

bool	ft_pip_check(char *str)
{
	if (str[0] == '|')
		return (true);
	return (false);
}

bool	ft_heredoc(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (true);
	return (false);
}

bool	ft_redirect_in(char *str)
{
	if (str[0] == '<' && str[1] != '<')
		return (true);
	return (false);
}
