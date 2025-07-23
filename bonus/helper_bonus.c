/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:54:00 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/23 13:56:14 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	setup_pipe(int *pipe_fd, int cmd_index, int total_cmds)
{
	if (cmd_index < total_cmds - 1)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe failed");
			return (1);
		}
	}
	return (0);
}
