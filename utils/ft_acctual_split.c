
#include "../minishell.h"

int	dollar_case(char *s)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (s[i] == '\"' && !single_q)
			double_q = !double_q;
		else if (s[i] == '$' && s[i + 1] && ft_strchr("\'\"", s[i + 1]) \
		&& !double_q && !single_q)
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_words(char *s)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (ft_is_space(*s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_is_space(*s))
			s++;
	}
	return (count);
}

char	**a_split(char *s)
{
	char	**str;
	size_t	i;
	size_t	r;
	size_t	j;

	if (!s)
	{
		str = ft_malloc(sizeof(char *), ALLOC);
		str[0] = NULL;
		return (str);
	}
	str = ft_malloc(sizeof(char *) * (count_words(s) + 1), ALLOC);
	(1) && (i = 0, j = 0);
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (s[i] && !ft_is_space(s[i]))
		{
			r = i;
			while (s[i] && !ft_is_space(s[i]))
				i++;
			str[j++] = subs(s, r, i - r);
		}
	}
	return (str[j] = NULL, str);
}
