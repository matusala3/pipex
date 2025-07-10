/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:45:27 by magebreh          #+#    #+#             */
/*   Updated: 2025/05/12 14:03:39 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	print_pointer(va_list *args)
{
	void			*ptr;
	uintptr_t		n;
	char			*hex_str;
	int				len;

	ptr = va_arg(*args, void *);
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	n = (uintptr_t) ptr;
	hex_str = ft_utoa_hex(n, LOWERCASE);
	if (hex_str == NULL)
		return (-1);
	write(1, "0x", 2);
	write(1, hex_str, ft_strlen(hex_str));
	len = ft_strlen(hex_str);
	free(hex_str);
	return (2 + len);
}
