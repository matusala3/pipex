/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:38:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/23 18:04:15 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pipe_fd[2];
	int		exit_status;

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
	exit_status = execute_pipeline(&pipex);
	return (exit_status);
}

int	execute_pipeline(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1, status2;

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
	if (waitpid(pid1, &status1, 0) == -1)
		perror("waitpid failed for cmd1");
	if (waitpid(pid2, &status2, 0) == -1)
		perror("waitpid failed for cmd2");
	
	// Return exit status of last command (cmd2)
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}

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
		perror("Failed to open infile");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for stdin");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for stdout");
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
}
