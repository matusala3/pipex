/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:56:38 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/24 19:53:55 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child1_process(t_pipex *pipex)
{
	char	**cmd_args;
	char	*cmd_path;

	child1_redirect(pipex);
	cmd_args = ft_split(pipex->cmd1, ' ');
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

void	child1_redirect(t_pipex *pipex)
{
	int	fd_in;

	fd_in = open(pipex->infile, O_RDONLY);
	if (fd_in < 0)
	{
		perror(pipex->infile);
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
}

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
		perror(pipex->outfile);
		exit(EXIT_FAILURE);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
