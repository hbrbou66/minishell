/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraji <abrajistudent.1337>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:10:51 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 03:10:52 by abraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	getcwd_fail(char *path, t_env **env, char **hold_pwd, char *newpwd)
{
	char	*av[3];

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

void	update_oldpwd(t_env **env, char *oldpwd)
{
	char	*av[3];

	av[0] = ft_strdup("export");
	av[1] = strj("OLDPWD=", oldpwd);
	av[2] = NULL;
	ft_export(av, env, 1);
}

static char	*prepare_oldpwd(t_env **env)
{
	char	*oldpwd;
	char	*env_pwd;

	oldpwd = getcwd(NULL, 0);
	env_pwd = get_env_value(env, "PWD");
	if (!oldpwd)
		oldpwd = ft_strdup2(env_pwd);
	else
	{
		if (env_pwd && env_pwd[0] == '\0')
			update_oldpwd(env, "");
		else
			update_oldpwd(env, oldpwd);
	}
	return (oldpwd);
}

int	change_dir(char *path, t_env **env, char **hold_pwd)
{
	char	*oldpwd;
	char	*newpwd;
	char	*av[3];

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

char	*ft_cd(char **opt, t_env **env)
{
	char		*home;
	static char	*hold_pwd;

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
