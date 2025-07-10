/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:47:11 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/09 13:25:39 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	int fd1;
	int fd2;
	int num_cmds;
	int here_doc;

	if(argc < 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	here_doc = (!ft_strncmp(argv[1], "here_doc", 9));
	num_cmds = argc - 3;
	if(here_doc)
	{
		
	}
	else
	{
		fd1 = open(argv[1], O_RDONLY);
		if(fd1 == -1)
		{
			perror("failed to open file1!");
			return (2);
		}
		fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd2 == -1)
		{
			perror("failed to open file2!");
			return (2);
		}
		close(fd1);
		close(fd2);
		return (0);
	}
	
}
