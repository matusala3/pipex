/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:11 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/10 15:58:41 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	int fd1;
	int fd2;

	pipex.here_doc = (!ft_strncmp(argv[1], "here_doc", 9));
	if ((pipex.here_doc && argc < 6) || (!pipex.here_doc && argc < 5)) {
		ft_printf("Usage: ./pipex [here_doc LIMITER] file1 cmd1 ... cmdn file2\n");
		return (1);
	}
	pipex.num_cmds = argc - 3 - pipex.here_doc;
	pipex.outfile = argv[argc - 1];
	pipex.cmds = &argv[2 + pipex.here_doc];
	pipex.envp = envp;
	if (pipex.here_doc)
	{
		pipex.infile = NULL;
		pipex.limiter = argv[2];
	}
	else
	{
		pipex.limiter = NULL;
		pipex.infile = argv[1];
	}
	execute_pipeline(&pipex);
	return (0);
}

void execute_pipeline(t_pipex *pipex)
{
	int i;
	int hd_pipe[2];
	int prev_fd;

	i = 0;
	while (i < pipex->num_cmds)
	{
		if(i == 0 && pipex->here_doc)
		{
			if(init_here_doc_pipe(pipex, hd_pipe) != 0)
				exit_with_error();
			prev_fd = hd_pipe[0];
		}
		else if(i == 0 && !pipex->here_doc)
		{
			prev_fd = open(pipex->infile, O_RDONLY);
			if(prev_fd < 0)
				perror("failed to open infile!");
		}
		if (i < pipex->cmds - 1)
		
		i++;
	}
	
}

init_here_doc_pipe(t_pipex *pipex, int pipe_fd[2])
{
	
}
