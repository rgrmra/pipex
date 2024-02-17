/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/02/16 20:19:11 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**ft_getenv(char **env, char *var)
{
	size_t	size;

	if (!env || !var)
		return (0);
	size = ft_strlen(var);
	while (*env && ft_strncmp(*env, var, size))
		env++;
	if (!(*env))
		return (0);
	return (ft_split(*env + size + 1, ':'));
}

static void	erase_command(t_cmd *cmd)
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
	if (data -> flag == O_APPEND)
		unlink(HEREDOC);
	if (data -> fds)
	{
		i = 0;
		while (data -> fds[i])
			free(data -> fds[i++]);
		free(data -> fds);
	}
	free(data -> path);
	free(data);
	data = 0;
}

static int	pipex(t_data *data)
{
	int	status;

	status = 0;
	while (data -> cmdnbr++ < data -> argc)
	{
		if (pipe(data -> fds[data -> cmdnbr - 2]))
			ft_error(data, "pipe", strerror(errno), 130);
		data -> pid = fork();
		if (data -> pid < 0)
			ft_error(data, "fork", "Failed to initiate", 1);
		if (data -> pid == 0 && data -> cmdnbr == 2)
			child(data, INFILE);
		else if (data -> pid == 0 && data -> cmdnbr == data -> argc)
			child(data, OUTFILE);
		else if (data -> pid == 0)
			child(data, MIDFILE);
		if (data -> cmdnbr > 2)
			close_fds(data -> fds[data -> cmdnbr - 3]);
	}
	close_fds(data -> fds[data -> cmdnbr - 3]);
	waitpid(data -> pid, &status, WUNTRACED);
	erase_data(data);
	if (((status) & 0x7f) == 0)
		return (((status) & 0xff00) >> 8);
	return ((status) & 0x7f);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if ((argc < 6 && argv[1] && strncmp(argv[1], DOCNAME, 9) == 0) || argc < 5)
		ft_error(0, "pipex", "Too few arguments", 1);
	data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_error(0, "pipex", "Failed to allocate memory", 1);
	data -> path = ft_getenv(envp, "PATH");
	data -> cmdnbr = 1;
	data -> argc = argc - 2;
	data -> argv = argv;
	data -> envp = envp;
	data -> flag = O_TRUNC;
	alloc_fds(data);
	data -> infile = *(argv + 1);
	data -> outfile = *(argv + argc - 1);
	if (ft_strncmp(*(argv + 1), DOCNAME, 9) == 0)
		data -> infile = here_doc(data);
	return (pipex(data));
}
