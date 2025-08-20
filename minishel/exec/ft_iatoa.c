/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iatoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbou-dou <hbou-dou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 03:11:43 by abraji            #+#    #+#             */
/*   Updated: 2025/08/19 17:47:26 by hbou-dou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str, int *flag)
{
	unsigned long (res) = 0;
	int (sig) = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sig *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*(str++) - 48);
		if (res - 1 > 9223372036854775807 && sig == -1)
			return (*flag = 1, 0);
		if (res > 9223372036854775807 && sig == 1)
			return (*flag = 1, -1);
	}
	*flag = 0;
	return ((int)res * sig);
}

static size_t	len(long nb)
{
	size_t (i) = 0;
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long (num) = n;
	int (n_len) = len(num);
	int (flag) = 0;
	char *(s);
	if (!n)
		return (ft_strdup("0"));
	else if (num < 0)
		(1) && (n_len++, flag = 1, num *= -1);
	s = ft_malloc(n_len + 1, ALLOC);
	if (flag == 1)
		s[0] = '-';
	s[n_len] = '\0';
	n_len--;
	while (n_len >= flag)
	{
		s[n_len] = num % 10 + 48;
		num /= 10;
		n_len--;
	}
	return (s);
}
