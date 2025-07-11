/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:11 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/11 16:24:47 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

	if (argc < 2)
	{
		ft_printf("Usage: ./pipex [here_doc LIMITER] infile cmd1 ... cmdN outfile\n");
		return (1);
	}

    if (parse_arguments(&pipex, argc, argv, envp) != 0)
        return (1);

    // if (execute_pipeline(&pipex) != 0)
    //     return (2);

    // cleanup_pipex(&pipex);
    return (0);
}


int parse_arguments(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if ((argc < 5 && ft_strncmp(argv[1], "here_doc", 9) != 0) ||
		(argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0)) 
	{
		ft_printf("Usage: ./pipex [here_doc LIMITER] infile cmd1 ... cmdN outfile\n");
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

int init_here_doc_pipe(t_pipex *pipex)
{
	(void) pipex;
	return 1;
}

int execute_pipeline(t_pipex *pipex)
{
	int i;
	int pipe_fd[2];
	int fd_in;
	int pid;

	i = 0;
	if(pipex->here_doc == 1)
		fd_in = init_here_doc_pipe(pipex);
	else
		fd_in = open(pipex->infile, O_RDONLY);

	while (i < pipex->num_cmds)
	{
		if (i < pipex->num_cmds - 1)
        	pipe(pipe_fd);
		pid = fork();
		if(pid == 0)
			launch_child(pipex, i, fd_in, pipe_fd);
		close(fd_in);
		if(i < pipex->num_cmds - 1)
			close(pipe_fd[1]);
		fd_in = pipe_fd[0];
		i++;
	}
	return (0);
}


void launch_child(t_pipex *pipex, int i, int prev_fd, int pipe_fd[2])
{
	int fd_out;

	dup2(prev_fd, STDIN_FILENO);
	if(i == pipex->num_cmds - 1)
	{
		fd_out = open(pipex->outfile, O_WRONLY | O_CREAT, 0644);
		dup2(fd_out, STDOUT_FILENO);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	char **cmd_args = ft_split(pipex->cmds[i], ' ');
	char *path = get_command_path(cmd_args[0], pipex->envp);
	if (!path)
	{
		perror("command not found");
		exit(1);
	}
	execve(path, cmd_args, pipex->envp);

}

// void execute_pipeline(t_pipex *pipex)
// {
// 	int i;
// 	int pid;
// 	int pipe_fd[2];
// 	int prev_fd;

// 	i = 0;
// 	while (i < pipex->num_cmds)
// 	{
// 		if (i == 0)
// 		{
// 			if (pipex->here_doc)
// 			{
// 				if (init_here_doc_pipe(pipex, pipe_fd) != 0)
// 					exit_with_error();
// 				prev_fd = pipe_fd[0];
// 			}
// 			else
// 			{
// 				prev_fd = open(pipex->infile, O_RDONLY);
// 				if (prev_fd < 0)
// 					perror("failed to open infile");
// 			}
// 		}

// 		if (i < pipex->num_cmds - 1)
// 			pipe(pipe_fd);

// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			// 👇 Now write CHILD LOGIC here (dup2, execve, close)
// 		}

// 		// 🔁 PARENT LOGIC (close prev_fd and pipe_fd[1])
// 		// Save pipe_fd[0] to prev_fd for next loop

// 		i++;
// 	}
	
// }

// init_here_doc_pipe(t_pipex *pipex, int pipe_fd[2])
// {
	
// }
