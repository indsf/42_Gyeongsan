/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:51:12 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:40:31 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
0일때만 heredoc을 먼저 열거임      
	//열건데 delimite의 heredoc_env_expand 값에 따라 환경변수 확장할건지 판단
이 후에 0일때만 openfile을 해야댐

s_parser를 s_execve로 변환하기 */

static int	execute_heredoc(t_data *data, t_token *cur_token, int write_fd)
{
	char	*str;
	char	*tmp;

	g_signal_code = 0;
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (error_print("warning: here-document \
				delimited by end-of-file", 0), 0);
		if (!ft_strcmp(str, cur_token->cmd))
			return (free(str), 0);
		if (cur_token->quotes == ZERO_QUEOTES && cmd_env_check(str))
		{
			tmp = str;
			str = env_expand(data->env, str);
			free(tmp);
			if (!str)
				return (errno);
		}
		if (write(write_fd, str, ft_strlen(str)) < 0 || write(write_fd, "\n",
				1) < 0)
			return (free(str), errno);
		free(str);
	}
	return (g_signal_code);
}

static int	redir_add(char *filename, int fd, t_parser *cur_parser)
{
	t_redir	*new;

	new = redir_new(filename, fd, HEREDOC);
	if (!new)
		return (1);
	redir_add_back(&(cur_parser->in), new);
	return (0);
}

static int	child_process(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		g_signal_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_signal_code = WTERMSIG(status) + 128;
	}
	return (0);
}

static int	fork_heredoc(t_data *data, t_parser *parser, t_token *cur_token,
		t_parser *cur_parser)
{
	pid_t	pid;
	int		fd[2];
	int		exit_code;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (close(fd[0]), close(fd[1]), 1);
	else if (pid == 0)
	{
		heredoc_signal();
		close(fd[0]);
		exit_code = execute_heredoc(data, cur_token->next, fd[1]);
		close(fd[1]);
		parser_clear(&parser);
		exit_error(data, exit_code, 0);
	}
	reset_signal();
	close(fd[1]);
	if (child_process(pid) || \
		redir_add(cur_token->next->cmd, fd[0], cur_parser))
		return (close(fd[0]), 1);
	return (main_signal(), 0);
}

int	open_heredoc(t_data *data, t_parser *parser)
{
	t_parser	*cur_parser;
	t_token		*cur_token;

	cur_parser = parser;
	while (cur_parser)
	{
		cur_token = cur_parser->token;
		while (cur_token)
		{
			if (cur_token->quotes == ZERO_QUEOTES && \
				cur_token->cmd[0] == '<' && cur_token->cmd[1] == '<')
			{
				if (fork_heredoc(data, parser, cur_token, cur_parser))
				{
					parser_clear(&parser);
					exit_error(data, 0, 1);
				}
				if (g_signal_code == 130)
					return (1);
			}
			cur_token = cur_token->next;
		}
		cur_parser = cur_parser->next;
	}
	return (0);
}
