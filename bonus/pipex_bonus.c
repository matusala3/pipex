/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:11 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/15 22:52:53 by magebreh         ###   ########.fr       */
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

int	init_here_doc_pipe(t_pipex *pipex)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	ft_printf("pipe heredoc> ");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)) == 0
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
