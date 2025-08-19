/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraji <abrajistudent.1337>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:12:07 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 03:12:08 by abraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_and_oldpwd(t_env *env, int fd)
{
	char	*from_cd;
	t_env	*pwd_env;

	pwd_env = find_env(env, "PWD");
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
	char	*a;

	a = getcwd(NULL, 0);
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
