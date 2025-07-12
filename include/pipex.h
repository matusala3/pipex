/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:38:46 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/12 22:49:18 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "../libft/libft.h"

typedef struct s_pipex
{
    char	*infile;
	char	*outfile;
	char 	*cmd1;
	char	*cmd2;
	char	*envp;
	int		pipe_fd[2];
}	t_pipex;



#endif