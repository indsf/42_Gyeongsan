/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:51:55 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/03 19:02:51 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_find_path(char **envp)
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

void	ft_free(char **ex_path_split)
{
	int	i;

	i = 0;
	while (ex_path_split[i])
	{
		free(ex_path_split[i]);
		i++;
	}
	free(ex_path_split);
	return ;
}

char	*ft_access_cmd(char *cmd, char **envp)
{
	int		i;
	char	*path_join;
	char	*ans_excute;
	char	**ex_path;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		write(2, "No such file or directory\n", 26);
		return (NULL);
	}
	ex_path = ft_split(ft_find_path(envp), ':');
	while (ex_path[i])
	{
		path_join = ft_strjoin(ex_path[i], "/");
		ans_excute = ft_strjoin(path_join, cmd);
		free(path_join);
		if (access(ans_excute, F_OK | X_OK) == 0)
			return (ft_free(ex_path), ans_excute);
		i++;
		free(ans_excute);
	}
	return (ft_free(ex_path), NULL);
}

void	ft_cmd_excute(char *argv, char **envp)
{
	char	**cmd_split;
	char	*excute_path;

	cmd_split = ft_split(argv, ' ');
	if (!cmd_split || !cmd_split[0])
	{
		ft_free(cmd_split);
		write(2, "Command not found\n", 18);
		exit(127);
	}
	excute_path = ft_access_cmd(cmd_split[0], envp);
	if (!excute_path)
	{
		ft_free(cmd_split);
		write(2, "Command not found\n", 18);
		exit(127);
	}
	if (execve(excute_path, cmd_split, envp) == -1)
	{
		ft_free(cmd_split);
		write(2, "Command not found\n", 18);
		exit(127);
	}
}
