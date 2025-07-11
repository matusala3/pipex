/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:16 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/11 16:23:44 by magebreh         ###   ########.fr       */
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
int execute_pipeline(t_pipex *pipex);
void launch_child(t_pipex *pipex, int i, int prev_fd, int pipe_fd[2]);
int init_here_doc_pipe(t_pipex *pipex);

char *get_path_variable(char **envp);
char *get_command_path(char *cmd, char **envp);
char *join_path(char **folders, char *cmd);
void free_split(char **split);

#endif