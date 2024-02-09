/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:56:19 by rde-mour          #+#    #+#             */
/*   Updated: 2024/02/09 15:56:36 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(t_data *data, char *bin, char *error, int status)
{
	char	*message;
	int		size;

	if (!bin)
		bin = "";
	size = ft_sprintf(&message, "pipex: %s: %s\n", bin, error);
	write(STDERR_FILENO, message, size);
	free(message);
	if (data && data -> fds && status >= 2 && data -> cmdnbr - 2 > 0)
		close_fds(data -> fds[data -> cmdnbr - 2]);
	if (data && data -> fds && status >= 2 && data -> cmdnbr - 3 > 0)
		close_fds(data -> fds[data -> cmdnbr - 3]);
	if (data)
		erase_data(data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (status == EACCES)
		status = 126;
	else if (status == ENOENT)
		status = 127;
	exit(status);
}

static void	get_command(t_data **data, char *args)
{
	int		fd;
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
	if (!cmd -> bin)
		return ;
	fd = open(cmd -> bin, O_DIRECTORY | O_RDONLY, 0644);
	if (fd != -1)
	{
		close(fd);
		if (cmd -> bin && ft_strchr(cmd -> bin, '/'))
			ft_error(*data, (*data)-> cmd -> bin, "Is a directory", 126);
		ft_error(*data, (*data)-> cmd -> bin, "command not found", 127);
	}
}

static void	execute_command(t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	path = 0;
	get_command(&data, *(data -> argv + data -> cmdnbr));
	while (data -> path && *(data -> path + i))
	{
		ft_sprintf(&path, "%s/%s", *(data -> path + i++), data -> cmd -> bin);
		if (path && access(path, F_OK | X_OK) == 0
			&& execve(path, data -> cmd -> flags, data -> envp) < 0)
		{
			free(path);
			ft_error(data, data -> cmd -> bin, strerror(errno), errno);
		}
		free(path);
	}
	if (data -> cmd -> bin
		&& access(data -> cmd -> bin, F_OK) == 0
		&& execve(data -> cmd -> bin, data -> cmd -> flags, data -> envp) < 0)
		ft_error(data, data -> cmd -> bin, strerror(errno), errno);
	if (data -> cmd -> bin && ft_strchr(data -> cmd -> bin, '/'))
		ft_error(data, data -> cmd -> bin, "No such file or directory", 127);
	ft_error(data, data -> cmd -> bin, "command not found", 127);
}

void	child(t_data *data, int signal)
{
	if (signal == INFILE)
	{
		open_file(data, signal);
		dup2(data -> fds[data -> cmdnbr - 2][PIPE_IN], STDOUT_FILENO);
		close_fds(data -> fds[data -> cmdnbr - 2]);
		dup2(data -> fdin, STDIN_FILENO);
		close(data -> fdin);
	}
	else if (signal == OUTFILE)
	{
		open_file(data, signal);
		dup2(data -> fds[data -> cmdnbr - 3][PIPE_OUT], STDIN_FILENO);
		close_fds(data -> fds[data -> cmdnbr - 3]);
		dup2(data -> fdout, STDOUT_FILENO);
		close(data -> fdout);
	}
	execute_command(data);
}
