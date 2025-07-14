/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:37:37 by magebreh          #+#    #+#             */
/*   Updated: 2025/07/14 15:19:07 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void free_string_array(char **split)
{
    int i;

    if (!split)
        return;
    i = 0;
    while(split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

char *get_path_var(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}

char *get_cmd_path(char *cmd, char **envp)
{
    char *path_var;
    char **folders;
    char *exec_path;

    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);   
    }
    path_var = get_path_var(envp);
    if (!path_var)
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    folders = ft_split(path_var, ':');
    if (!folders)
        return (NULL);
    exec_path = join_paths(folders, cmd);
    free_string_array(folders);
    if (!exec_path)
        return (NULL);
    return (exec_path);
}

char *join_paths(char **folders, char *cmd)
{
    int i;
    char *temp;
    char *exec_path;

    i = 0;
    while (folders[i])
    {
        temp = ft_strjoin(folders[i], "/");
        if (!temp)
            return (NULL);
        exec_path = ft_strjoin(temp, cmd);
        free(temp);
        if (!exec_path)
            return (NULL);
        if (access(exec_path, X_OK) == 0)
            return (exec_path);
        free(exec_path);
        i++;
    }
    return (NULL);
}