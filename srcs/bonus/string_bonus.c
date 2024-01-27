/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:53:03 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/27 19:55:01 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	find_double_quotte(char **str)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (*str && *(*(str) + i))
	{
		if (*(*(str) + i) == '\"' && c == '\a')
			c = ' ';
		else if (*(*(str) + i) == '\"' && c == ' ')
			c = '\a';
		if (*(*(str) + i) == ' ')
			*(*(str) + i) = c;
		else if (*(*(str) + i) == '\"')
			*(*(str) + i) = ' ';
		i++;
	}
}

void	ft_split_quotte(char *str, char ***splitted)
{
	int		i;

	find_double_quotte(&str);
	i = 0;
	while (*str && *(str + i))
	{
		if ((*(str + i) == '\'' && *(str + i + 1) == ' ')
			|| (*(str + i) == '\'' && *(str + i + 1) == '\0')
			|| (i > 0 && *(str + i - 1) == ' ' && *(str + i) == '\'')
			|| (i == 0 && *(str + i) == '\''))
			*(str + i) = '\"';
		i++;
	}
	find_double_quotte(&str);
	*splitted = ft_split(str, ' ');
	i = 0;
	while (*(*(splitted) + i))
		ft_strrplc(*(*(splitted) + i++), '\a', ' ');
	free(str);
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
	close(fds[PIPE_IN]);
	close(fds[PIPE_OUT]);
}

void	open_file(t_data *data, int signal)
{
	if (signal == INFILE)
	{
		data -> fdin = open(data -> infile, O_RDONLY, 0644);
		if (data -> fdin < 0)
			ft_error(data, data -> infile, strerror(errno), 1);
		return ;
	}
	if (signal != OUTFILE)
		return ;
	data->fdout = open(data -> outfile, data -> flag | O_RDWR | O_CREAT, 0644);
	if (data -> fdout < 0)
		ft_error(data, data -> outfile, strerror(errno), 1);
}
