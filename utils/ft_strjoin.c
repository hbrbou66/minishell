/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraji <abraji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:59:51 by abraji            #+#    #+#             */
/*   Updated: 2025/08/16 04:01:09 by abraji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strj(char *s1, char *s2)
{
	char	*string;
	size_t	len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	string = ft_malloc(len, ALLOC);
	ft_strlcpy(string, s1, len);
	ft_strlcat(string, s2, len);
	return (string);
}
