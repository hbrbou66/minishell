/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:10:51 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:04 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_oldpwd(t_env **env, char *oldpwd)
{
	char *(av)[3];
	av[0] = ft_strdup("export");
	av[1] = strj("OLDPWD=", oldpwd);
	av[2] = NULL;
	ft_export(av, env, 1);
}

static char	*prepare_oldpwd(t_env **env)
{
	char *(oldpwd);
	char *(env_pwd);
	env_pwd = get_env_value(env, "PWD");
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup2(env_pwd);
	else
	{
		if (env_pwd[0] == '\0' && env_pwd)
			update_oldpwd(env, "");
		else
			update_oldpwd(env, oldpwd);
	}
	return (oldpwd);
}

int	change_dir(char *path, t_env **env, char **hold_pwd)
{
	char *(av)[3];
	char *(newpwd);
	char *(oldpwd);
	oldpwd = prepare_oldpwd(env);
	if (chdir(path) == -1)
		return (free(oldpwd), e_status(1, 2), perror("cd"), 1);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		getcwd_fail(path, env, hold_pwd, newpwd);
	else
	{
		*hold_pwd = ft_strdup(newpwd);
		av[0] = ft_strdup("export");
		av[1] = strj("PWD=", newpwd);
		av[2] = NULL;
		ft_export(av, env, 1);
		free(newpwd);
	}
	free(oldpwd);
	return (0);
}

void	getcwd_fail(char *path, t_env **env, char **hold_pwd, char *newpwd)
{
	char *(av)[3];
	(void)newpwd;
	ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories\n", 2);
	newpwd = ft_strdup(path);
	if (!ft_strcmp(path, ".") || !ft_strcmp(path, ".."))
	{
		av[0] = ft_strdup("export");
		if (find_env(*env, "PWD"))
			av[1] = strj("PWD+=/", path);
		else
		{
			av[1] = strj("PWD=", strj(*hold_pwd, "/.."));
			*hold_pwd = av[1];
		}
		av[2] = NULL;
		ft_export(av, env, 1);
	}
}

char	*ft_cd(char **opt, t_env **env)
{
	static char *(hold_pwd);
	char *(home);
	if (!opt && !env)
		return (hold_pwd);
	if (!opt[1])
	{
		home = get_env_value(env, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2),
				e_status(1, 1), NULL);
		return (change_dir(home, env, &hold_pwd), NULL);
	}
	if (opt[1] && opt[2] == NULL)
		return (change_dir(opt[1], env, &hold_pwd), NULL);
	else if (opt[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2),
			e_status(1, 1), NULL);
	return (NULL);
}
