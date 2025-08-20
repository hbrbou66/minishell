/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:10:59 by abraji            #+#    #+#             */
/*   Updated: 2025/08/20 00:24:24 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*init_env(char **envp)
{
	t_env *(env) = NULL;
	char *(equal), *(key), *(value);
	while (*envp && envp)
	{
		equal = ft_strchr(*envp, '=');
		if (equal)
		{
			key = subs(*envp, 0, equal - *envp);
			value = ft_strdup(equal + 1);
		}
		else
			(1) && (key = ft_strdup(*envp), value = NULL);
		ft_lstadd_back_exec(&env, ft_lstnew_exec(key, value));
		envp++;
	}
	return (env);
}

char	*get_env_value(t_env **env, char *path)
{
	t_env *(tmp) = find_env(*env, path);
	char *(value);
	if (!tmp)
		return (NULL);
	value = ft_strdup(tmp->value);
	return (value);
}

int	ft_env(t_env *env, int fd)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
	return (0);
}
