/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:53:56 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:44:58 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_signal(char *cmd)
{
	if (ft_strstr(cmd, "minishell"))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		signal(SIGQUIT, handler);
	recevied_from_input(1, 1);
}

char	*get_env(char *val, t_env *envp)
{
	char *(sub_var), *(result);
	int (processed);
	t_env *(tmp);
	processed = variable_skip(val, 0);
	sub_var = subs(val, 1, processed - 1);
	if (!ft_strcmp(sub_var, "?"))
		return (ft_itoa(e_status(0, 0)));
	tmp = find_env(envp, sub_var);
	if (!tmp)
		return (NULL);
	result = tmp->value;
	if (!result[0])
		return (NULL);
	return (result);
}

void	default_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

int	check_exp_type(t_tokentype type)
{
	if (type == EXPAN || type == SINGLE_Q || type == DOUBLE_Q || type == WORD)
		return (1);
	return (0);
}
