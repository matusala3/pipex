/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:10:58 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/23 18:03:40 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	execute_command(t_pipex *pipex, int i)
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(pipex->cmds[i], ' ');
	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
		write(STDERR_FILENO, ": command not found\n", 20);
		if (cmd_args)
			free_string_array(cmd_args);
		exit(127);
	}
	path = get_command_path(cmd_args[0], pipex->envp);
	if (!path)
	{
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		free_string_array(cmd_args);
		exit(127);
	}
	execve(path, cmd_args, pipex->envp);
	perror(cmd_args[0]);
	free(path);
	free_string_array(cmd_args);
	exit(127);
}

void	launch_child(t_pipex *pipex, int i, int prev_fd, int pipe_fd[2])
{
	int	fd_out;

	if (dup2(prev_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for stdin");
		exit(1);
	}
	close(prev_fd);
	if (i == pipex->num_cmds - 1)
	{
		fd_out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("Failed to open outfile!");
			exit(1);
		}
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for stdout");
			exit(1);
		}
		close(fd_out);
	}
	else
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for stdout");
			exit(1);
		}
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	execute_command(pipex, i);
}

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

int	init_here_doc_pipe(t_pipex *pipex)
{
	int		pipe_fd[2];
	char	*line;
	size_t	limiter_len;

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	limiter_len = ft_strlen(pipex->limiter);
	ft_printf("pipe heredoc> ");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strlen(line) == limiter_len + 1 
			&& ft_strncmp(line, pipex->limiter, limiter_len) == 0
			&& line[ft_strlen(pipex->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		ft_printf("pipe heredoc> ");
		line = get_next_line(0);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
