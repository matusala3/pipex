/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:16 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/10 17:37:17 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
#define FT_PIPEX_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <../libft/libft.h>
#include "../ft_printf/ft_printf.h"

typedef struct s_pipex {
    int     here_doc;
    int     num_cmds;
    char    *infile;
    char    *outfile;
    char    **cmds;
    char    **envp;
    char    *limiter;
}   t_pipex;

int parse_arguments(t_pipex *pipex, int argc, char **argv, char **envp);

#endif