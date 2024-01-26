/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:56:19 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/25 17:30:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	erase_command(t_cmd *cmd)
{
	size_t	i;

	if (!cmd)
		return ;
	i = 0;
	if (cmd -> flags)
		while (*(cmd -> flags + i))
			free(*(cmd -> flags + i++));
	if (cmd -> flags)
		free(cmd -> flags);
	free(cmd);
	cmd = 0;
}

void	erase_data(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data)
		return ;
	while (*(data -> path + i))
		free(*(data -> path + i++));
	if (data -> cmd)
		erase_command(data -> cmd);
	free(data -> path);
	free(data);
	data = 0;
}

void	ft_error(t_data *data, char *bin, char *error, int status)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("pipex: %s: %s\n", bin, error);
	if (status == 0 && data -> fdin > -1)
		return ;
	erase_data(data);
	exit(status);
}

void	child(t_data *data, int signal, int fds[], char *argv)
{
	if (signal == INFILE)
	{
		dup2(fds[PIPE_IN], STDOUT_FILENO);
		dup2(data -> fdin, STDIN_FILENO);
	}
	else if (signal == OUTFILE)
	{
		dup2(fds[PIPE_OUT], STDIN_FILENO);
		dup2(data -> fdout, STDOUT_FILENO);
	}
	close(fds[PIPE_IN]);
	close(fds[PIPE_OUT]);
	close(data -> fdin);
	close(data -> fdout);
	get_command(&data, argv);
	execute_command(data);
}
