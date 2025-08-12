
#include "../minishell.h"

int	count_until_pipe(t_token *lst)
{
	int	count;

	count = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type == WORD)
			count++;
		lst = lst->next;
	}
	return (count);
}

void	handle_word(t_token *lst, t_exec *node, int *i)
{
	node->cmd_args[*i] = ft_strdup(lst->value);
	if (*i == 0)
		node->cmd = node->cmd_args[0];
	(*i)++;
}

void	check_word(t_token **lst, t_exec *node, int *i)
{
	if ((*lst)->value)
		handle_word(*lst, node, i);
	if (ft_strstr((*lst)->value, "minishell"))
	{
		while ((*lst))
			*lst = (*lst)->next;
	}
}

int	fill_node(t_token **lst, t_exec *node)
{
	int		i;
	int		ac;

	(1) && (i = 0, ac = count_until_pipe(*lst));
	node->cmd_args = ft_malloc(sizeof(char *) * (ac + 1), ALLOC);
	while (*lst && (*lst)->type != PIPE)
	{
		if ((*lst)->type == WORD)
			check_word(lst, node, &i);
		else if ((*lst)->type == HERDOC)
		{
			if ((*lst)->fd_reder == -1)
				node->flag = 1;
			node->fd_in = (*lst)->fd_reder;
		}
		else
			if (handle_redirects(lst, node))
				node->flag = 1;
		if (*lst && (*lst)->type != PIPE)
			*lst = (*lst)->next;
	}
	return (node->cmd_args[i] = NULL, 0);
}

t_exec	*convert_token_to_exec(t_token *lst, t_env *env)
{
	t_exec	*head;
	t_exec	*node;
	t_token	*tmp;

	(1) && (tmp = lst, head = NULL);
	while (lst)
	{
		node = new_node();
		(fill_node(&lst, node), add_back(&head, node));
		if (lst && lst->type == PIPE)
			lst = lst->next;
	}
	if (ft_stop_redirect(tmp, env))
	{
		while (head)
		{
			if (head->fd_in != 0)
				close(head->fd_in);
			if (head->fd_out > 2)
				close(head->fd_out);
			head = head->next;
		}
		return (NULL);
	}
	return (head);
}
