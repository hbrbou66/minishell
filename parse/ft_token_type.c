
#include "../minishell.h"

bool	ft_check_pip(char *string)
{
	if (string[0] == '|')
		return (true);
	return (false);
}

bool	ft_check_redirect_in(char *string)
{
	if (string[0] == '<' && string[1] != '<')
		return (true);
	return (false);
}

bool	ft_check_redirect_out(char *string)
{
	if (string[0] == '>' && string[1] != '>')
		return (true);
	return (false);
}

bool	ft_check_append(char *string)
{
	if (string[0] == '>' && string[1] == '>')
		return (true);
	return (false);
}

bool	ft_check_heredoc(char *string)
{
	if (string[0] == '<' && string[1] == '<')
		return (true);
	return (false);
}
