/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:56:19 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/22 22:21:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (status == 0)
		return ;
	erase_data(data);
	exit(status);
}

void	child(t_data *data, int signal, int fds1[], int fds2[])
{
	if (signal == INFILE)
	{
		dup2(fds1[PIPE_IN], STDOUT_FILENO);
		close(fds1[PIPE_OUT]);
		dup2(data -> fdin, STDIN_FILENO);
		close(data -> fdin);
	}
	else if (signal == OUTFILE)
	{
		dup2(fds1[PIPE_OUT], STDIN_FILENO);
		close(fds1[PIPE_IN]);
		dup2(data -> fdout, STDOUT_FILENO);
		close(data -> fdout);
	}
	else if (signal == MIDFILE)
	{
		dup2(fds1[PIPE_OUT], STDIN_FILENO);
		close(fds1[PIPE_IN]);
		dup2(fds2[PIPE_IN], STDOUT_FILENO);
		close(fds2[PIPE_OUT]);
	}
	get_command(&data, *(data -> argv));
	execute_command(data);
}
