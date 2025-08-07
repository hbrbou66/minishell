
#include "../minishell.h"

int	ft_check_quotes_type(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == '\'')
			return (SINGLE);
		if (string[index] == '\"')
			return (COUPLE);
		index++;
	}
	return (0);
}
