/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/22 18:30:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	get_command(t_data **data, char *args)
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

void	execute_command(t_data *data)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (data -> path && *(data -> path + i))
	{
		tmp = ft_strjoin(*(data -> path + i++), "/");
		path = ft_strjoin(tmp, data -> cmd -> bin);
		if (path && access(path, F_OK && X_OK) == 0)
		{
			if (execve(path, data -> cmd -> flags, data -> envp) < 0)
			{
				free(tmp);
				free(path);
				ft_error(data, data -> cmd -> bin, strerror(errno), 127);
			}
		}
		free(tmp);
		free(path);
	}
	if (data -> cmd -> bin && access(data -> cmd -> bin, F_OK && X_OK) == 0)
		if (execve(data -> cmd -> bin, data -> cmd -> flags, data -> envp) < 0)
			ft_error(data, data -> cmd -> bin, strerror(errno), 127);
	ft_error(data, data -> cmd -> bin, "command not found", 127);
}

static int	pipex(t_data *data)
{
	int	status;

	if (pipe(data -> fds))
		ft_error(data, "pipe", "Failed to initiate", 1);
	data -> pidin = fork();
	if (data -> pidin < 0)
		ft_error(data, "fork", "Failed to initiate", 1);
	if (data -> pidin == 0)
		child(data, INFILE, data -> fds, data -> argv[2]);
	data -> pidout = fork();
	if (data -> pidout < 0)
		ft_error(data, "fork", "Failed to initiate", 1);
	if (data -> pidout == 0)
		child(data, OUTFILE, data -> fds, data -> argv[3]);
	close(data -> fds[0]);
	close(data -> fds[1]);
	waitpid(data -> pidin, 0, 0);
	waitpid(data -> pidout, &status, 0);
	erase_data(data);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5 && argc > 5)
		ft_error(0, "pipex", "Too many arguments", 1);
	else if (argc < 5)
		ft_error(0, "pipex", "Too few arguments", 1);
	data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!data)
		ft_error(0, "pipex", "Failed to allocate memory", 1);
	data -> path = ft_getenv(envp, "PATH");
	data -> argv = argv;
	data -> envp = envp;
	data -> fdin = open(argv[1], O_RDONLY, 0644);
	if (data -> fdin < 0)
		ft_error(data, argv[1], strerror(errno), 0);
	data -> fdout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data -> fdout < 0)
		ft_error(data, argv[argc - 1], strerror(errno), 1);
	return (pipex(data));
}
