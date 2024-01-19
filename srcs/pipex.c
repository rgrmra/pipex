/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/19 14:57:52 by rde-mour         ###   ########.org.br   */
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

static void	getcmd(t_data **data, char *args)
{
	t_cmd	*cmd;
	char	**splited;

	if (!data || !args)
		return ;
	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return ;
	splited = ft_split(args, ' ');
	cmd -> flags = splited;
	cmd -> bin = *splited;
	(*data) -> cmd = cmd;
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
			path = ft_strjoin(tmp, data -> cmd -> bin);
			if (access(path, F_OK && X_OK) == 0)
			{
				ft_printf("\033[0;92m%s\033[0;m\n", path);
				execve(path, data -> cmd -> flags, env);
			}
			free(tmp);
			free(path);
		}
	}
	else
		waitpid(pid, 0, 0);
}

static void	erasecmd(t_cmd *cmd)
{
	size_t	i;

	if (!cmd)
		return ;
	i = 0;
	while (*(cmd -> flags + i))
		free(*(cmd -> flags + i++ ));
	free(cmd -> flags);
	free(cmd);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_data	*data;

	if (argc < 5)
		return (1);
	data = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!data)
		return (-1);
	data -> path = ft_getenv(env, "PATH");
	data -> input = argv[1];
	data -> output = argv[argc - 1];
	i = 2;
	while (i < argc - 1)
	{
		getcmd(&data, argv[i++]);
		execcmd(data, env);
		erasecmd(data -> cmd);
	}
	i = 0;
	while (*(data -> path + i))
		free(*(data -> path + i++));
	free(data -> path);
	free(data);
	return (0);
}
