/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:38 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:01 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd_in_path(char **arr, char *cmd)
{
	char *(tmp);
	int (i) = 0;
	while (arr[i] && !is_empty(cmd))
	{
		tmp = strj(arr[i], "/");
		tmp = strj(tmp, cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char *path)
{
	char **(arr), *(tmp);
	if (!cmd)
		exit(e_status(0, 0));
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (cmd_not_found(cmd), NULL);
	}
	arr = ft_split_exec(path, ':');
	if (!arr)
		return (NULL);
	tmp = find_cmd_in_path(arr, cmd);
	if (tmp)
		return (tmp);
	return (cmd_not_found(cmd), NULL);
}
