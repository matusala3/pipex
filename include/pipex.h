/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:16 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/09 13:25:31 by magebreh         ###   ########.fr       */
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
#include "../ft_printf/ft_printf.h"

typedef struct s_pipex {
    int     here_doc;
    int     num_cmds;
    char    *infile;
    char    *outfile;
    char    **cmds;
    char    **envp;
}   t_pipex;


#endif