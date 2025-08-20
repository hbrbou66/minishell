/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acctual_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:59:29 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 15:55:07 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_words(char *s)
{
	size_t (count) = 0;
	if (!*s)
		return (0);
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

static void	populate_split(char **str, char *s, size_t *j)
{
	size_t (i) = 0;
	size_t (r);
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!ft_is_space(s[i]) && s[i])
		{
			r = i;
			while (!ft_is_space(s[i]) && s[i])
				i++;
			str[(*j)++] = subs(s, r, i - r);
		}
	}
}

char	**a_split(char *s)
{
	char **(str);
	size_t (j);
	int (leading), (extra);
	if (!s)
	{
		str = ft_malloc(sizeof(char *), ALLOC);
		str[0] = NULL;
		return (str);
	}
	leading = ft_is_space(s[0]);
	extra = 0;
	if (leading)
		extra++;
	str = ft_malloc(sizeof(char *) * (count_words(s) + 1 + extra), ALLOC);
	j = 0;
	if (leading)
		str[j++] = ft_strdup("");
	populate_split(str, s, &j);
	return (str[j] = NULL, str);
}

int	dollar_case(char *s)
{
	int (i) = 0;
	int (single_q) = 0;
	int (double_q) = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (s[i] == '\"' && !single_q)
			double_q = !double_q;
		else if (s[i] == '$' && s[i + 1] && ft_strchr("\'\"", s[i + 1])
			&& !double_q && !single_q)
			return (1);
		i++;
	}
	return (0);
}
