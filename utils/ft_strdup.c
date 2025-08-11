
#include "../minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*res;

	if (!src)
		return (NULL);
	res = ft_malloc(ft_strlen(src) + 1, ALLOC);
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
