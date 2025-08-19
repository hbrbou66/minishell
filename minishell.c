/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:05:16 by abraji            #+#    #+#             */
/*   Updated: 2025/08/17 20:05:08 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (!recevied_from_input(0, 0))
		ft_putstr_fd("\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	if (!recevied_from_input(0, 0))
		rl_redisplay();
	else
		recevied_from_input(0, 1);
	e_status(130, 1);
	(void)sig;
}

void	define_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
}

void	check_argc(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell: please provide only one argument\n", 2);
		exit(127);
	}
}

void	init_shell(t_shell *shell_ctx, char **env)
{
	shell_ctx->input = NULL;
	shell_ctx->expn = NULL;
	shell_ctx->lst = NULL;
	shell_ctx->exec = NULL;
	shell_ctx->envp = init_env(env);
}

int	main(int argc, char **argv, char **env)
{
	t_shell (shell_ctx);
	check_argc(argc);
	(1) && (init_shell(&shell_ctx, env), argv = NULL);
	while (1)
	{
		define_sig();
		recevied_from_input(0, 1);
		shell_ctx.input = \
		readline("minishell-> ");
		if (!shell_ctx.input)
			return (ft_putstr_fd("exit\n", 1), free(shell_ctx.input),
				ft_malloc(0, CLEAR_DATA), e_status(0, 0));
		if (*shell_ctx.input)
			add_history(shell_ctx.input);
		if (ft_parse_command(shell_ctx.input))
			continue ;
		shell_ctx.lst = s_cmd(ft_split(shell_ctx.input), shell_ctx.envp);
		if (!shell_ctx.lst || ft_expand(shell_ctx.lst, shell_ctx.envp))
			continue ;
		shell_ctx.exec = convert_token_to_exec(shell_ctx.lst);
		if (!shell_ctx.exec)
			continue ;
		execution(shell_ctx.exec, &shell_ctx.envp);
	}
	return (0);
}
