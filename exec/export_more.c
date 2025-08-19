/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:33 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 20:06:14 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_imbguous(t_token **lst, t_exec *node)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	if ((*lst)->next->ambg)
	{
		if (node->fd_in > 0)
			close(node->fd_in);
		if (node->fd_out > 2)
			close(node->fd_out);
		skip_till_pipe(lst);
		return (ambigous_red(), 1);
	}
	return (0);
}

int	is_valid_export(char *opt)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(opt[i]) || opt[i] == '_'))
		return (1);
	i++;
	while (opt[i])
	{
		if (!(ft_isalnum(opt[i]) || opt[i] == '_'))
		{
			if (opt[i] == '+' && opt[i + 1] == '=')
				return (0);
			else if (opt[i] == '=')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	bubble_sort_env(t_env *env)
{
	int		swap;
	t_env	*ptr;

	if (!env)
		return ;
	swap = 1;
	while (swap)
	{
		swap = 0;
		ptr = env;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_env(ptr, ptr->next);
				swap = 1;
			}
			ptr = ptr->next;
		}
	}
}

void	print_sorted_env(t_env *env, int fd)
{
	bubble_sort_env(env);
	while (env)
	{
		if (env->key && !ft_strcmp("_", env->key))
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env->key, fd);
		if (env->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
}
