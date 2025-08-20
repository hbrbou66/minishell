/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:59:41 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 16:16:29 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	acttual_len(char *s, int i)
{
	int (start) = i;
	char (c);
	while (s[i])
	{
		if (ft_strchr("|<>", s[i]))
			return (i - start);
		else if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
			if (!s[i])
				return (i - start);
		}
		else if (ft_is_space(s[i]))
			break ;
		i++;
	}
	return (i - start);
}

int	skip_spaces(char *s, int i)
{
	while (s[i] && ft_is_space(s[i]))
		i++;
	return (i);
}

int	get_word_len(char *s, int i)
{
	int (start) = i;
	if (s[i] == '|')
		return (1);
	if (ft_strchr("<>", s[i]))
	{
		while (ft_strchr("<>", s[i]) && s[i])
			i++;
		return (i - start);
	}
	return (acttual_len(s, i));
}

int	ft_countword(char *s)
{
	int (i) = 0;
	int (count) = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		i += get_word_len(s, i);
		count++;
	}
	return (count);
}

char	**ft_split(char *s)
{
	int (i) = 0;
	int (j) = 0;
	int (word_len);
	int (words) = ft_countword(s);
	char **(lst);
	if (words == 0)
		return (free(s), NULL);
	lst = ft_malloc(sizeof(char *) * (words + 1), ALLOC);
	if (!lst)
		return (free(s), NULL);
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break ;
		word_len = get_word_len(s, i);
		lst[j++] = subs(s, i, word_len);
		i += word_len;
	}
	lst[j] = NULL;
	return (free(s), lst);
}
