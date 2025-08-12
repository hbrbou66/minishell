
#include "../minishell.h"

bool	handle_quotes(char *s, t_expand *e)
{
	if (s[e->index] == '\'' && !e->double_q)
	{
		e->single_q = !e->single_q;
		e->index++;
		return (true);
	}
	else if (s[e->index] == '\"' && !e->single_q)
	{
		e->double_q = !e->double_q;
		e->index++;
		return (true);
	}
	return (false);
}

void	init_expand_vars(char **nv, t_expand *e, bool *reset)
{
	*nv = NULL;
	e->index = 0;
	e->single_q = false;
	e->double_q = false;
	*reset = true;
}

void	first_expand(t_expand_ctx *c)
{
	t_var	*list;

	list = s_var(c->s);
	while (list)
	{
		if (!ft_strcmp(list->value, "$?"))
			list->value = ft_itoa(e_status(0, 0));
		else if (!ft_strcmp(list->value, "$"))
			list->value = list->value;
		else if (list->type == VAR)
			list->value = g_env(list->value, c->envp);
		else
			list->value = ft_remove_quotes(c, list->value);
		c->nv = strj(c->nv, list->value);
		list = list->next;
	}
}

void	init_expan(t_expand_ctx *ctx, char *s, t_env *envp)
{
	ctx->nv = NULL;
	ctx->e.index = 0;
	ctx->e.single_q = false;
	ctx->e.double_q = false;
	ctx->r = true;
	ctx->envp = envp;
	ctx->s = s;
}

char	*exp_val(char *s, t_env *envp)
{
	t_expand_ctx	ctx;

	init_expan(&ctx, s, envp);
	first_expand(&ctx);
	return (ctx.nv);
}
