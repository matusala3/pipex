/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:38:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/21 13:05:11 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pipe_fd[2];

	if (argc != 5)
	{
		ft_printf("./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	pipex.infile = argv[1];
	pipex.outfile = argv[4];
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	pipex.envp = envp;
	if (pipe(pipe_fd) == -1)
	{
		perror("piping failed!");
		exit(1);
	}
	pipex.pipe_fd[0] = pipe_fd[0];
	pipex.pipe_fd[1] = pipe_fd[1];
	execute_pipeline(&pipex);
	return (0);
}

void	execute_pipeline(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Fork failed for cmd1");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		child1_process(pipex);
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Fork failed for cmd2");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		child2_process(pipex);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}

void	child1_process(t_pipex *pipex)
{
	char	**cmd_args;
	char	*cmd_path;

	child1_redirect(pipex);
	cmd_args = ft_split(pipex->cmd1, ' ');
	if (!cmd_args)
	{
		perror("Failed to split command");
		exit(EXIT_FAILURE);
	}
	cmd_path = get_cmd_path(cmd_args[0], pipex->envp);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "Command not found: ", 19);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, "\n", 1);
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
		perror("Failed to open infile");
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
	if (!cmd_args)
	{
		perror("Failed to split command");
		exit(EXIT_FAILURE);
	}
	cmd_path = get_cmd_path(cmd_args[0], pipex->envp);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "Command not found: ", 19);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, "\n", 1);
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
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
