/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:38:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/12 23:02:18 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
    t_pipex	pipex;
    int		pipe_fd[2];

	if(argc != 5)
	{
		ft_printf("./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	pipex.infile = argv[1];
	pipex.outfile = argv[4];
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	pipex.envp = envp;
	if(pipe(pipe_fd) == -1)
	{
		perror("piping failed!");
		exit(1);
	}
	pipex.pipe_fd[0] = pipe_fd[0];
	pipex.pipe_fd[1] = pipe_fd[1];
	
}