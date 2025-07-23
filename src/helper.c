/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:56:38 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/23 18:04:30 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child2_process(t_pipex *pipex)
{
	char	**cmd_args;
	char	*cmd_path;

	child2_redirect(pipex);
	cmd_args = ft_split(pipex->cmd2, ' ');
	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
		write(STDERR_FILENO, ": command not found\n", 20);
		if (cmd_args)
			free_string_array(cmd_args);
		exit(127);
	}
	cmd_path = get_cmd_path(cmd_args[0], pipex->envp);
	if (!cmd_path)
	{
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		free_string_array(cmd_args);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd_args, pipex->envp);
	perror("execve failed");
	free_string_array(cmd_args);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

void	child2_redirect(t_pipex *pipex)
{
	int	fd_out;

	fd_out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror("Failed to open outfile");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for stdout");
		exit(EXIT_FAILURE);
	}
	close(fd_out);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed for stdin");
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
