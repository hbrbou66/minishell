/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:54:07 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 20:52:16 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_check;

void	heredoc_signal(int sig)
{
	(void)sig;
	close(0);
	recevied_from_input(1, 1);
	write(1, "\n", 1);
	rl_on_new_line();
	g_check = 1;
}

char	*ft_herdoc_expand(char *val, t_env *envp)
{
	char *(n_v) = NULL, *(s) = NULL;
	int (i) = 0, (b_i) = 0;
	bool (reset) = true;
	while (val[i])
	{
		if (reset)
			{
				b_i = i;
				reset = false;
			}
		if (val[i] == '$' && val[i + 1] && check_id(val + i + 1))
		{
			(1) && (s = subs(val, b_i, i - b_i), n_v = strj(n_v, s));
			(1) && (s = get_env(val + i, envp), i += variable_skip(val, i));
			(1) && (n_v = strj(n_v, s), reset = true);
		}
		else if (!val[i + 1])
			(1) && (i++, s = subs(val, b_i, i - b_i), \
			n_v = strj(n_v, s));
		else
			i++;
	}
	return (n_v);
}

int	ft_heredoc_handle(t_token *lst, t_env *env, int fd_out)
{
	char *(input), *(expanded);
	int (fd);

	if (fd_out == -1)
		return (1);
	g_check = 0;
	fd = dup(STDIN_FILENO);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, lst->next->value))
			break ;
		if (ft_strchr(input, '$') && !lst->next->heredoc_expn)
			expanded = ft_herdoc_expand(input, env);
		else
			expanded = input;
		ft_putstr_fd(expanded, fd_out);
		write(fd_out, "\n", 1);
		free(input);
	}
	if (g_check)
		return (free(input), dup2(fd, STDIN_FILENO), close(fd_out), \
		close(fd), e_status(130, 1), 1);
	return (close(fd_out), close(fd), e_status(0, 1), free(input), 0);
}
