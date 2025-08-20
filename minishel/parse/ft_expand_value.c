/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:53:51 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:14:20 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_expan(t_expand_ctx *ctx, char *str, t_env *envp)
{
	ctx->new_value = NULL;
	ctx->expand_state.index = 0;
	ctx->expand_state.single_q = false;
	ctx->expand_state.double_q = false;
	ctx->reset_flag = true;
	ctx->envp = envp;
	ctx->source_string = str;
}

void	start_expand(t_expand_ctx *ctx)
{
	t_var	*var_list;

	var_list = s_var(ctx->source_string);
	while (var_list)
	{
		if (!ft_strcmp(var_list->value, "$?"))
			var_list->value = ft_itoa(e_status(0, 0));
		else if (!ft_strcmp(var_list->value, "$"))
			var_list->value = var_list->value;
		else if (var_list->type == VAR)
			var_list->value = get_env(var_list->value, ctx->envp);
		else
			var_list->value = ft_remove_quotes(ctx, var_list->value);
		ctx->new_value = strj(ctx->new_value, var_list->value);
		var_list = var_list->next;
	}
}

char	*exp_val(char *str, t_env *envp)
{
	t_expand_ctx (context);
	init_expan(&context, str, envp);
	start_expand(&context);
	return (context.new_value);
}

bool	handle_quotes(char *str, t_expand *exp)
{
	if (str[exp->index] == '\'' && !exp->double_q)
	{
		exp->single_q = !exp->single_q;
		exp->index++;
		return (true);
	}
	else if (str[exp->index] == '\"' && !exp->single_q)
	{
		exp->double_q = !exp->double_q;
		exp->index++;
		return (true);
	}
	return (false);
}
