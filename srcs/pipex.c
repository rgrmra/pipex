/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:32:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/17 19:50:59 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	i;

	if (argc < 2 || argv[1] == (void *)0)
		return (1);
	i = 0;
	while (*(env + i))
		ft_printf("%s\n", *(env + i++));
	return (0);
}
