/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:38:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/24 17:34:37 by magebreh         ###   ########.fr       */
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
	int		status1;
	int		status2;

	fork_processes(pipex, &pid1, &pid2);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}

int	fork_processes(t_pipex *pipex, pid_t *pid1, pid_t *pid2)
{
	*pid1 = fork();
	if (*pid1 < 0)
	{
		perror("Fork failed for cmd1");
		exit(EXIT_FAILURE);
	}
	if (*pid1 == 0)
		child1_process(pipex);
	*pid2 = fork();
	if (*pid2 < 0)
	{
		perror("Fork failed for cmd2");
		exit(EXIT_FAILURE);
	}
	if (*pid2 == 0)
		child2_process(pipex);
	return (0);
}