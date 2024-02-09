/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:53:03 by rde-mour          #+#    #+#             */
/*   Updated: 2024/02/07 21:22:48 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_split_quotte(char *tmp, char ***splitted)
{
	int		i;
	char	sign;

	i = -1;
	sign = 0;
	while (tmp && *(tmp + ++i))
	{
		if (sign && *(tmp + i) == sign)
		{
			*(tmp + i) = ' ';
			sign = 0;
		}
		else if (!sign && (*(tmp + i) == '\"' || *(tmp + i) == '\''))
		{
			sign = *(tmp + i);
			*(tmp + i) = ' ';
		}
		else if (sign && *(tmp + i) == ' ')
			*(tmp + i) = 0x1A;
	}
	*splitted = ft_split(tmp, ' ');
	i = 0;
	while (*(*(splitted) + i))
		ft_strrplc(*(*(splitted) + i++), 0x1A, ' ');
	free(tmp);
}

void	alloc_fds(t_data *data)
{
	int	i;

	data -> fds = (int **) ft_calloc(data -> argc, sizeof(int **));
	if (!(data -> fds))
		ft_error(data, "file descriptors", "Failed to allocate memory", 1);
	i = 0;
	while (i < data -> argc - 1)
	{
		data -> fds[i] = (int *) ft_calloc(2, sizeof(int));
		if (!(data -> fds[i++]))
			ft_error(data, "file descriptors", "Failed to allocate memory", 1);
	}
}

void	close_fds(int fds[])
{
	if (!fds)
		return ;
	close(fds[PIPE_IN]);
	close(fds[PIPE_OUT]);
	fds = 0;
}

void	open_file(t_data *data, int signal)
{
	if (signal == INFILE)
	{
		data -> fdin = open(data -> infile, O_RDONLY, 0644);
		if (data -> fdin < 0)
		{
			close_fds(data -> fds[data -> cmdnbr - 2]);
			ft_error(data, data -> infile, strerror(errno), 1);
		}
		return ;
	}
	if (signal != OUTFILE)
		return ;
	data->fdout = open(data -> outfile, O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (data -> fdout < 0)
	{
		close_fds(data -> fds[data -> cmdnbr - 2]);
		close_fds(data -> fds[data -> cmdnbr - 3]);
		ft_error(data, data -> outfile, strerror(errno), 1);
	}
}
