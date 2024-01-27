/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:56:19 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/27 12:26:46 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(t_data *data, char *bin, char *error, int status)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("pipex: %s: %s\n", bin, error);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	if (status == 0 && data -> fdin > -1)
		return ;
	erase_data(data);
	exit(status);
}

static void	get_command(t_data **data, char *args)
{
	t_cmd	*cmd;
	char	**splitted;

	if (!data || !args)
		return ;
	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return ;
	ft_split_quotte(ft_strdup(args), &splitted);
	cmd -> flags = splitted;
	cmd -> bin = *splitted;
	(*data)-> cmd = cmd;
}

static void	execute_command(t_data *data)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	get_command(&data, *(data -> argv + data -> cmdnbr));
	while (data -> path && *(data -> path + i))
	{
		tmp = ft_strjoin(*(data -> path + i++), "/");
		path = ft_strjoin(tmp, data -> cmd -> bin);
		free(tmp);
		if (path && access(path, F_OK | X_OK) == 0)
		{
			if (execve(path, data -> cmd -> flags, data -> envp) < 0)
			{
				free(path);
				ft_error(data, data -> cmd -> bin, strerror(errno), 127);
			}
		}
		free(path);
	}
	if (data -> cmd -> bin && access(data -> cmd -> bin, F_OK | F_OK) == 0)
		if (execve(data -> cmd -> bin, data -> cmd -> flags, data -> envp) < 0)
			ft_error(data, data -> cmd -> bin, strerror(errno), 127);
	ft_error(data, data -> cmd -> bin, "command not found", 127);
}

void	child(t_data *data, int signal)
{
	if (signal == INFILE)
	{
		dup2(data -> fds[data -> cmdnbr - 2][PIPE_IN], STDOUT_FILENO);
		dup2(data -> fdin, STDIN_FILENO);
		close_fds(data -> fds[data -> cmdnbr - 2]);
	}
	else if (signal == OUTFILE)
	{
		dup2(data -> fds[data -> cmdnbr - 3][PIPE_OUT], STDIN_FILENO);
		close_fds(data -> fds[data -> cmdnbr - 3]);
		dup2(data -> fdout, STDOUT_FILENO);
	}
	else if (signal == MIDFILE)
	{
		dup2(data -> fds[data -> cmdnbr - 3][PIPE_OUT], STDIN_FILENO);
		close_fds(data -> fds[data -> cmdnbr - 3]);
		dup2(data -> fds[data -> cmdnbr - 2][PIPE_IN], STDOUT_FILENO);
		close_fds(data -> fds[data -> cmdnbr - 2]);
	}
	close(data -> fdin);
	close(data -> fdout);
	execute_command(data);
}

char	*here_doc(t_data *data)
{
	char	*tmp;

	data -> flag = O_APPEND;
	data -> fdin = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data -> fdin < 0)
		ft_error(data, data -> argv[data -> argc], strerror(errno), 1);
	while (1)
	{
		ft_printf("> ");
		tmp = get_next_line(STDIN_FILENO);
		if (tmp && strncmp(tmp, data -> argv[2], ft_strlen(tmp) - 1) == 0)
			break ;
		ft_putstr_fd(tmp, data -> fdin);
		free(tmp);
	}
	free(tmp);
	data -> argv++;
	data -> argc--;
	close(data -> fdin);
	return (HEREDOC);
}
