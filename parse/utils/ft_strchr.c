
#include "../../minishell.h"

char	*ft_strchr( char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && (*s != c))
		s++;
	if (*s == c)
		return (s);
	return (NULL);
}
