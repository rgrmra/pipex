/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/20 22:04:44 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	erasecmd(t_cmd *cmd)
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

void	erasedata(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data)
		return ;
	while (*(data -> path + i))
		free(*(data -> path + i++));
	if (data -> cmd)
		erasecmd(data -> cmd);
	free(data -> path);
	free(data);
	data = 0;
}

void	ft_error(t_data *data, char *error)
{
	erasedata(data);
	if (errno)
		perror("Error");
	else
		ft_putendl_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

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

static void	getcmd(t_data **data, char *args)
{
	t_cmd	*cmd;
	char	**splitted;

	if (!data || !args)
		return ;
	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return ;
	splitted = ft_split(args, ' ');
	cmd -> flags = splitted;
	cmd -> bin = *splitted;
	(*data)-> cmd = cmd;
}

void	execcmd(t_data *data)
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
			if (execve(path, data -> cmd -> flags, data -> envp) < 0)
				ft_error(data, "");
		free(tmp);
		free(path);
	}
	if (data -> cmd -> bin && access(data -> cmd -> bin, F_OK && X_OK) == 0)
		if (execve(data -> cmd -> bin, data -> cmd -> flags, data -> envp) < 0)
			ft_error(data, "");
	ft_error(data, "Error: No such file or directory");
}

void	a(t_data *data)
{
	if (!data)
		return ;
	dup2(data -> fds[PIPE_IN], STDOUT_FILENO);
	close(data -> fds[PIPE_OUT]);
	dup2(data -> fdin, STDIN_FILENO);
	close(data -> fdin);
	getcmd(&data, data -> argv[2]);
	execcmd(data);
}

void	c(t_data *data)
{	
	if (data)
		printf("%d\n", data -> argc);
}

void	b(t_data *data)
{
	if (!data)
		return ;
	dup2(data -> fds[PIPE_OUT], STDIN_FILENO);
	close(data -> fds[PIPE_IN]);
	dup2(data -> fdout, STDOUT_FILENO);
	close(data -> fdout);
	getcmd(&data, data -> argv[3]);
	execcmd(data);
}

void	pipex(t_data *data)
{
	if (pipe(data -> fds))
		perror("pipe");
	data -> pidin = fork();
	if (data -> pidin < 0)
		perror("pid");
	if (data -> pidin == 0)
		a(data);
	if (data -> argc > 1)
		c(data);
	data -> pidout = fork();
	if (data -> pidout < 0)
		perror("pid");
	if (data -> pidout == 0)
		b(data);
	close(data -> fds[0]);
	close(data -> fds[1]);
	waitpid(data -> pidin, 0, 0);
	waitpid(data -> pidout, 0, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5 && argc > 5)
		ft_error(0, "Error: Too many arguments.");
	else if (argc < 5)
		ft_error(0, "Error: Too few arguments.");
	data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!data)
		perror("data");
	data -> path = ft_getenv(envp, "PATH");
	data -> argc = argc - 3;
	data -> argv = argv;
	data -> envp = envp;
	data -> fdin = open(argv[1], O_RDONLY, 0644);
	if (data -> fdin < 0)
		ft_error(data, "Error: Invalid input file.");
	data -> fdout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data -> fdout < 0)
		ft_error(data, "Error: Invalid output file.");
	pipex(data);
	erasedata(data);
	return (0);
}
