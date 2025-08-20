/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:12:07 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:32 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_and_oldpwd(t_env *env, int fd)
{
	char *(from_cd);
	t_env *(pwd_env) = find_env(env, "PWD");
	if (!pwd_env)
	{
		from_cd = ft_cd(NULL, NULL);
		if (!from_cd)
			return (perror("pwd"), 1);
		ft_putstr_fd(from_cd, fd);
		ft_putstr_fd("\n", fd);
		return (0);
	}
	else
	{
		ft_putstr_fd(pwd_env->value, fd);
		ft_putstr_fd("\n", fd);
		return (0);
	}
	return (1);
}

int	ft_pwd(t_env *env, int fd)
{
	char *(a) = getcwd(NULL, 0);
	if (a)
	{
		ft_putstr_fd(a, fd);
		ft_putstr_fd("\n", fd);
		free(a);
		return (0);
	}
	else
	{
		pwd_and_oldpwd(env, fd);
		return (0);
	}
	e_status(1, 1);
	return (1);
}
