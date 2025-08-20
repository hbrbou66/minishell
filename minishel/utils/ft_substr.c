/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraji <abraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 04:00:04 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 04:01:17 by abraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*subs(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	tot_len;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s) || !len)
		return (NULL);
	if (len > ft_strlen(s + start))
		tot_len = ft_strlen(s + start) + 1;
	else
		tot_len = len + 1;
	str = ft_malloc(tot_len, ALLOC);
	ft_strlcpy(str, s + start, tot_len);
	return (str);
}
