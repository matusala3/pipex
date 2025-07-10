/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:45:20 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/10 17:53:00 by magebreh         ###   ########.fr       */
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

static char	*ft_utoa(unsigned int n)
{
	int		len;
	char	*res;

	len = count_digits(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (res);
}

int	print_unsigned(va_list *args)
{
	int				i;
	unsigned int	n;
	char			*str;
	int				bytes;

	i = 0;
	bytes = 0;
	n = va_arg(*args, unsigned int);
	str = ft_utoa(n);
	if (!str)
		return (-1);
	while (str[i])
		i++;
	bytes = write(1, str, i);
	free(str);
	return (bytes);
}
