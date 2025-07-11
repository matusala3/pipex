/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:12:45 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/11 16:54:53 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_extract_line(char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_free(char *s1, const char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_read_to_buffer(int fd, char *leftovers, char *temp_buff);
void	ft_save_leftovers(char *buffer, char *leftovers);

#endif
