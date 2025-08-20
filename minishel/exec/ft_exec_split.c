/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:46 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:15 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_count_words(char *str, char c)
{
	size_t (i) = 0;
	size_t (rst) = 0;
	size_t (cnt) = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			rst = 0;
		else if (rst == 0)
		{
			rst = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

static char	*ft_strndup(char *str, size_t n)
{
	size_t (i) = 0;
	char *(s) = ft_malloc(n + 1, ALLOC);
	while (n--)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static int	ft_split_helper(int *i, char const *s, char c)
{
	int (start);
	while (s[*i] == c && (s[*i]))
		(*i)++;
	start = *i;
	while (s[*i] != c && (s[*i]))
		(*i)++;
	return (start);
}

char	**ft_split_exec(char const *s, char c)
{
	int (i) = 0;
	int (word) = 0;
	int (start) = 0;
	char **(strs);
	strs = ft_malloc((sizeof(char *)) * (ft_count_words((char *)s, c) + 1),
			ALLOC);
	while (s && s[i])
	{
		start = ft_split_helper(&i, s, c);
		if (i > start)
		{
			strs[word++] = ft_strndup((char *)s + start, i - start);
			if (!strs[word - 1])
				return (NULL);
		}
	}
	strs[word] = NULL;
	return (strs);
}
