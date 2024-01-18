/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/17 21:57:22 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**findenv(char **env, char *var)
{
	size_t	i;

	i = 0;
	while (ft_strncmp(*(env + i), var, 4))
		i++;
	return (ft_split(*(env + i), ':'));
}


int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**path;


	if (argc < 2 || argv[1] == (void *)0)
		return (1);
	path = findenv(env, "PATH");
	i = 0;
	while (*(path + i))
	{
		ft_printf("%s\n", *(path + i));
		free(*(path + i ));
		i++;
	}
	free(path);
	return (0);
}
