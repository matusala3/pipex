/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:11 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/21 15:19:49 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 2)
	{
		ft_printf("./pipex [here_doc LIMITER] infile cmd1 ... cmdN outfile\n");
		return (1);
	}
	if (parse_arguments(&pipex, argc, argv, envp) != 0)
		return (1);
	if (execute_pipeline(&pipex) != 0)
		return (2);
	return (0);
}

int	parse_arguments(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if ((argc < 5 && ft_strncmp(argv[1], "here_doc", 9) != 0)
		|| (argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0))
	{
		ft_printf("./pipex [here_doc LIMITER] infile cmd1 ... cmdN outfile\n");
		return (1);
	}
	pipex->here_doc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	pipex->num_cmds = argc - 3 - pipex->here_doc;
	pipex->outfile = argv[argc - 1];
	pipex->envp = envp;
	if (pipex->here_doc)
	{
		pipex->infile = NULL;
		pipex->limiter = argv[2];
		pipex->cmds = &argv[3];
	}
	else
	{
		pipex->limiter = NULL;
		pipex->infile = argv[1];
		pipex->cmds = &argv[2];
	}
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

int	exec_loop(t_pipex *pipex, int fd_in)
{
	int	i;
	int	*pids;
	int	status;
	int	pipe_fd[2];

	pids = malloc(sizeof(int) * pipex->num_cmds);
	if (!pids)
		return (1);
	loop(pipex, pids, fd_in, pipe_fd);
	i = 0;
	while (i < pipex->num_cmds)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	return (0);
}

int loop(t_pipex *pipex, int *pids, int fd_in, int pipe_fd[2])
{
	int	i;

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
}
