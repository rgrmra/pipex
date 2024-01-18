/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/18 15:57:33 by rde-mour         ###   ########.org.br   */
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

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_data	data;
	char	*tmp;
	pid_t	pid;

	if (argc < 2 || argv[1] == (void *)0)
		return (1);
	data.path = ft_getenv(env, argv[1]);
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (data.path && *(data.path + i))
		{
			tmp = ft_strjoin(*(data.path + i), "/");
			tmp = ft_strjoin(tmp, argv[2]);
			execve(tmp, &argv[2], env);
			free(tmp);
			i++;
		}
	}
	else
	{
		wait(&pid);
		while (data.path && *(data.path + i))
			free(*(data.path + i++));
	}
	free(data.path);
	return (0);
}
