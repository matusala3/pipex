/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:38:21 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/11 16:25:49 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char *get_path_variable(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return envp[i] + 5;
		i++;
	}
	return (NULL);
}

char *get_command_path(char *cmd, char **envp)
{
	int i;
	char *path_line;
	char **folders;
	char *exec_path;

	path_line = get_path_variable(envp);
	if (!path_line)
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		return NULL;
	}
	folders = ft_split(path_line, ':');
	i = 0;
	exec_path = join_path(folders, cmd);
	free_split(folders);
	if (exec_path)
		return exec_path;
	free_split(folders);
	if (access(cmd, X_OK) == 0)
    	return ft_strdup(cmd);
	return NULL;
}

char *join_path(char **folders, char *cmd)
{
	int i;
	char *temp;
	char *exec_path;

	i = 0;
	while (folders[i])
	{
		temp = ft_strjoin(folders[i], "/");
		exec_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(exec_path, X_OK) == 0)
			return exec_path;
		free(exec_path);
		i++;
	}
	return (NULL);
}

