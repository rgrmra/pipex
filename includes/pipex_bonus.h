/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:03:07 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/27 10:55:43 by rde-mour         ###   ########.org.br   */
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

# define HEREDOC "/tmp/heredoc"

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
	pid_t	pid;
	int		status;
	int		fds[100][2];
	int		flag;
	int		stderr;
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

void	child(t_data *data, int signal);
void	close_fds(int fds[]);
void	erase_data(t_data *data);
void	ft_error(t_data *data, char *bin, char *error, int status);
void	ft_split_quotte(char *str, char ***splitted);
char	*here_doc(t_data *data);

#endif
