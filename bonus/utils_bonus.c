/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:38:21 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/12 22:24:31 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	free_string_array(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_path_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**folders;
	char	*exec_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_path_variable(envp);
	if (!path_env)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	folders = ft_split(path_env, ':');
	exec_path = join_path(folders, cmd);
	free_string_array(folders);
	if (exec_path)
		return (exec_path);
	return (NULL);
}

char	*join_path(char **folders, char *cmd)
{
	int		i;
	char	*temp;
	char	*exec_path;

	i = 0;
	while (folders[i])
	{
		temp = ft_strjoin(folders[i], "/");
		exec_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}
