
#include "../minishell.h"

t_env	*ft_lstlast_exec(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_exec *exec)
{
	int	size;

	size = 0;
	while (exec)
	{
		size++;
		exec = exec->next;
	}
	return (size);
}

void	add_back(t_exec **head, t_exec *new)
{
	t_exec	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*ft_lstnew_exec(char *key, char *value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), ALLOC);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
