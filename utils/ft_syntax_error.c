
#include "../minishell.h"

void	ft_syntax_error(void)
{
	ft_putstr_fd("minishell : Syntax error\n", 2);
}

int	delimter(char *s, size_t index)
{
	if (index >= ft_strlen(s))
		return (0);
	while (1)
	{
		if (index > 0 && s[index] == '<' && s[index - 1] == '<')
			return (1);
		if (index == 0)
			break ;
		index--;
	}
	return (0);
}

int	check_env(char *v, t_env *e)
{
	t_expand	ex;

	(1) && (ex.index = 0, ex.double_q = false, ex.single_q = false, ex.start_index = 0);
	while (v[ex.index])
	{
		while (v[ex.index])
		{
			if (v[ex.index] == '=' && !ex.double_q && !ex.single_q)
				ex.start_index = 1;
			if (v[ex.index] == '$' && v[ex.index + 1] \
				&& id_check(v + ex.index + 1) && !ex.single_q && !ex.double_q)
				break ;
			if (v[ex.index] == '\'' && !ex.double_q)
				ex.single_q = !ex.single_q;
			else if (v[ex.index] == '\"' && !ex.single_q)
				ex.double_q = !ex.double_q;
			ex.index++;
		}
		if (!v[ex.index])
			break ;
		(1) && (ex.c = g_env(v + ex.index, e), ex.index += skip_variable(v, ex.index));
		if (check_for_s(ex.c) && !ex.start_index)
			return (1);
	}
	return (0);
}
