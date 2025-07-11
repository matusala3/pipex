/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:08:51 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/11 16:43:34 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "../libft.h"

# ifndef LOWERCASE
#  define LOWERCASE 0
# endif

# ifndef UPPERCASE
#  define UPPERCASE 1
# endif

typedef int	(*t_handler)(va_list *);
typedef struct s_specifier
{
	char		specifier;
	t_handler	handler;
}	t_specifier;

int		print_char(va_list *args);
int		print_string(va_list *args);
int		print_int(va_list *args);
int		print_unsigned(va_list *args);
int		print_hex_upper(va_list *args);
int		print_hex_lower(va_list *args);
int		print_pointer(va_list *args);
char	*ft_utoa_hex(uintptr_t n, int is_uppercase);
int		ft_printf(const char *format, ...);

#endif