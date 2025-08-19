/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraji <abrajistudent.1337>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:10:46 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 03:10:47 by abraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_t_env(t_env *env)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize_env(env);
	ret = ft_malloc(sizeof(char *) * (size + 1), ALLOC);
	while (env)
	{
		if (env->key && env->value)
		{
			tmp = strj(env->key, "=");
			ret[i] = strj(tmp, env->value);
			i++;
		}
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_exec *exec, t_env **env, bool forked)
{
	if (!ft_strcmp(exec->cmd, "echo") && !exec->flag)
		ft_echo(exec->cmd_args, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "cd") && !exec->flag)
		ft_cd(exec->cmd_args, env);
	else if (!ft_strcmp(exec->cmd, "pwd") && !exec->flag)
		ft_pwd(*env, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "export") && !exec->flag)
		ft_export(exec->cmd_args, env, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "unset") && !exec->flag)
		ft_unset(exec->cmd_args, env);
	else if (!ft_strcmp(exec->cmd, "env") && !exec->flag)
		ft_env(*env, exec->fd_out);
	else if (!ft_strcmp(exec->cmd, "exit") && !exec->flag)
		ft_exec_exit(exec->cmd_args, forked);
	if (forked)
		exit(e_status(0, 0));
}
