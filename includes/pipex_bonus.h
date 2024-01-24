/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:03:07 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/23 19:08:18 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

struct s_cmd
{
	char	*bin;
	char	**flags;
};

struct s_data
{
	char	**path;
	int		fdin;
	int		fdout;
	t_cmd	*cmd;
	int		cmdnbr;
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	pidin;
	pid_t	pidmid;
	pid_t	pidout;
	int		fds1[100][2];
};

enum e_pipe
{
	PIPE_OUT,
	PIPE_IN
};

enum e_signal
{
	INFILE,
	OUTFILE,
	MIDFILE
};

void	get_command(t_data **data, char *args);
void	execute_command(t_data *data);
void	erase_command(t_cmd *cmd);
void	erase_data(t_data *data);
void	ft_error(t_data *data, char *bin, char *error, int status);
void	child(t_data *data, int signal, int fds1[], int fds2[]);

#endif
