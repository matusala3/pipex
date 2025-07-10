/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:45:42 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/10 17:41:38 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa(int n)
{
	long	num;
	int		sign;
	int		len;
	char	*res;

	num = n;
	sign = (n < 0);
	len = count_digits(num) + sign;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	if (sign)
		num = -num;
	res[len] = '\0';
	while (len-- > sign)
	{
		res[len] = (num % 10) + '0';
		num /= 10;
	}
	if (sign)
		res[0] = '-';
	return (res);
}

int	print_int(va_list *args)
{
	int		n;
	char	*str;
	int		bytes;
	int		i;

	i = 0;
	bytes = 0;
	n = va_arg(*args, int);
	str = ft_itoa(n);
	if (!str)
		return (-1);
	while (str[i])
		i++;
	bytes = write(1, str, i);
	free(str);
	return (bytes);
}
