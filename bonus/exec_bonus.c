/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:10:58 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/15 23:14:10 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	setup_child_fds(t_pipex *pipex, int i, int prev_fd, int pipe_fd[2])
{
	int	fd_out;

	dup2(prev_fd, STDIN_FILENO);
	close(prev_fd);
	if (i == pipex->num_cmds - 1)
	{
		fd_out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("Failed to open outfile!");
			exit(1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	execute_command(t_pipex *pipex, int i)
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(pipex->cmds[i], ' ');
	if (!cmd_args)
	{
		perror("Command is empty or failed to split");
		exit(1);
	}
	path = get_command_path(cmd_args[0], pipex->envp);
	if (!path)
	{
		write(STDERR_FILENO, "bash: ", 6);
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
	setup_child_fds(pipex, i, prev_fd, pipe_fd);
	execute_command(pipex, i);
}

int	exec_loop(t_pipex *pipex, int fd_in)
{
	int	i;
	int	pipe_fd[2];
	int	*pids;
	int	status;

	pids = malloc(sizeof(int) * pipex->num_cmds);
	if (!pids)
		return (1);
	i = 0;
	while (i < pipex->num_cmds)
	{
		if (setup_pipe(pipe_fd, i, pipex->num_cmds) != 0)
		{
			free(pids);
			return (1);
		}
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork failed");
			free(pids);
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
	i = 0;
	while (i < pipex->num_cmds)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	return (0);
}

int	execute_pipeline(t_pipex *pipex)
{
	int	fd_in;

	if (pipex->here_doc == 1)
	{
		fd_in = init_here_doc_pipe(pipex);
		if (fd_in < 0)
		{
			perror("here_doc failed");
			return (1);
		}
	}
	else
	{
		fd_in = open(pipex->infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror("infile failed");
			return (1);
		}
	}
	return (exec_loop(pipex, fd_in));
}
