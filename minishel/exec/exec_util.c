/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:27 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:46:58 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	unsigned int (i) = 0;
	unsigned int (j) = 0;
	if (!str || !to_find)
		return (NULL);
	if (to_find[i] == '\0')
		return (str);
	while (str[i])
	{
		while (str[i + j] && str[i + j] == to_find[j])
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		i++;
		j = 0;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*s1 && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	is_empty(char *s)
{
	int (i) = 0;
	if (!s || !*s)
		return (1);
	while (s[i] && ft_is_space(s[i]))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

char	*ft_strdup2(char *src)
{
	int (i) = 0;
	char *(res);
	if (!src)
		return (NULL);
	res = malloc(ft_strlen(src) + 1);
	i = -1;
	while (src[++i])
		res[i] = src[i];
	res[i] = '\0';
	return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0 && s)
		write(fd, s, ft_strlen(s));
}
