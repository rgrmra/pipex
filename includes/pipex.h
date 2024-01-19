/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:44:33 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/19 13:45:16 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "ft_printf_bonus.h"
# include "get_next_line.h"
# include "libft.h"

typedef struct s_cmd	t_cmd;
typedef struct s_data	t_data;

struct s_data
{
	char	**path;
	t_cmd	*cmds;
	int		fds[2];
};

struct s_cmd
{
	char	*bin;
	char	**flags;
	t_cmd	*next;
};

void	pipex_lstadd_back(t_cmd **cmds, char *args);
void	pipex_lstclear(t_cmd **cmds);

#endif
