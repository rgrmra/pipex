/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/19 14:08:42 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_getenv(char **env, char *var)
{
	size_t	i;
	size_t	size;

	if (!env || !var)
		return (0);
	size = ft_strlen(var);
	i = 0;
	while (*(env + i) && ft_strncmp(*(env + i), var, size))
		i++;
	if (!*(env + i))
		return (0);
	return (ft_split(*(env + i) + size + 1, ':'));
}

static void	getcmds(t_data **data, char **args)
{
	size_t	i;

	if (!args)
		return ;
	i = 0;
	pipex_lstadd_back(&((*data)-> cmds), *(args + i++));
}

static void	execcmd(t_data *data, char **env)
{
	size_t	i;
	pid_t	pid;
	char	*tmp;
	char	*path;

	i = 0;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		while (data -> path && *(data -> path + i))
		{
			tmp = ft_strjoin(*(data -> path + i++), "/");
			path = ft_strjoin(tmp, data -> cmds -> bin);
			if (access(path, F_OK && X_OK) == 0)
				execve(path, data -> cmds -> flags, env);
			free(tmp);
			free(path);
		}
	}
	else
		waitpid(pid, 0, 0);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_data	*data;

	if (argc < 2 || argv[1] == (void *)0)
		return (1);
	data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!data)
		return (-1);
	data -> path = ft_getenv(env, "PATH");
	i = 1;
	while (i < argc)
	{
		getcmds(&data, &argv[i++]);
		execcmd(data, env);
		pipex_lstclear(&(data -> cmds));
	}
	i = 0;
	while (*(data -> path + i))
		free(*(data -> path + i++));
	free(data -> path);
	pipex_lstclear(&(data -> cmds));
	free(data);
	return (0);
}
