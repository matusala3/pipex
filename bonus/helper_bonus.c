/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:54:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/24 13:47:39 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	spawn_all(t_pipex *pipex, int *pids, int fd_in, int pipe_fd[2])
{
	int	i;

	i = 0;
	while (i < pipex->num_cmds)
	{
		if (setup_pipe(pipe_fd, i, pipex->num_cmds) != 0)
			return (1);
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork failed");
			return (1);
		}
		if (pids[i] == 0)
			launch_child(pipex, i, fd_in, pipe_fd);
		close(fd_in);
		if (i < pipex->num_cmds - 1)
			close(pipe_fd[1]);
		fd_in = pipe_fd[0];
		i++;
	}
	return (0);
}
