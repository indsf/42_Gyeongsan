/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:02:48 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/05 17:48:39 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_openfile(char *argv, int mode)
{
	int	file_mode;

	file_mode = 0;
	if (mode == 0)
	{
		file_mode = open(argv, O_RDONLY);
	}
	else if (mode == 1)
		file_mode = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		file_mode = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (file_mode);
}

int	ft_kind_process(int argc, char **argv, int *i)
{
	int	infile;

	infile = 0;
	if ((ft_strncmp(argv[1], "here_doc", 9) == 0))
	{
		if (argc <= 5)
			exit(1);
		infile = ft_heredoc(argv[2], ft_strlen(argv[2]));
		if (infile < 0)
			ft_perror_exit(NULL, 1);
		if (dup2(infile, STDIN_FILENO) == -1)
		{
			close(infile);
			perror("permission denied");
		}
		*i = 3;
	}
	else
	{
		infile = ft_openfile(argv[1], 0);
		if (infile < 0)
			perror("Permission denied");
		*i = 2;
	}
	return (infile);
}

pid_t	ft_last_argc(int argc, char **argv, char **envp, int saved_fd)
{
	pid_t	pid;
	int		out_f;

	out_f = ft_openfile(argv[argc - 1], ft_mode(argv));
	if (out_f < 0)
		perror("Permission denied");
	pid = fork();
	if (pid == -1)
		ft_perror_exit(NULL, 0);
	if (pid == 0)
	{
		if (out_f < 0)
			exit(1);
		if ((dup2(saved_fd, STDIN_FILENO) == -1) || (dup2(out_f,
					STDOUT_FILENO) == -1))
		{
			ft_close(out_f, saved_fd);
			ft_perror_exit(NULL, 0);
		}
		ft_close(out_f, saved_fd);
		ft_cmd_excute(argv[argc - 2], envp);
	}
	close(out_f);
	close(saved_fd);
	return (pid);
}

int	main(int argc, char **argv, char **envp)
{
	int			saved_fd;
	pid_t		process;
	pid_t		last_p;
	t_result	result;
	int			i;

	if (argc < 5)
		return (write(2, "error argc\n", 11), 1);
	i = 0;
	saved_fd = ft_kind_process(argc, argv, &i);
	while (i < argc - 2)
	{
		result = ft_process(argv[i++], envp, saved_fd);
		if (saved_fd >= 0)
			close(saved_fd);
		saved_fd = result.fd;
		process = result.pid;
	}
	last_p = ft_last_argc(argc, argv, envp, saved_fd);
	return (exit_main(process, last_p));
}
