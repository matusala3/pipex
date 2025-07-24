/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:38:46 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/24 13:51:05 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
	char	**envp;
	int		pipe_fd[2];
}	t_pipex;

char	*join_paths(char **folders, char *cmd);
char	*get_cmd_path(char *cmd, char **envp);
char	*get_path_var(char **envp);
void	free_string_array(char **split);
void	child2_redirect(t_pipex *pipex);
void	child1_process(t_pipex *pipex);
void	child1_redirect(t_pipex *pipex);
void	child2_process(t_pipex *pipex);
int		execute_pipeline(t_pipex *pipex);
int		fork_processes(t_pipex *pipex, pid_t *pid1, pid_t *pid2);

#endif