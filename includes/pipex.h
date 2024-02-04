/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:03:07 by rde-mour          #+#    #+#             */
/*   Updated: 2024/02/04 15:59:27 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "ft_printf_bonus.h"
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
	char	*infile;
	int		fdin;
	char	*outfile;
	int		fdout;
	t_cmd	*cmd;
	int		cmdnbr;
	int		argc;
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		status;
	int		**fds;
};

enum e_pipe
{
	PIPE_OUT,
	PIPE_IN
};

enum e_signal
{
	INFILE,
	OUTFILE
};

void	child(t_data *data, int signal);
void	close_fds(int fds[]);
void	erase_data(t_data *data);
void	alloc_fds(t_data *data);
void	ft_error(t_data *data, char *bin, char *error, int status);
void	ft_split_quotte(char *str, char ***splitted);
void	open_file(t_data *data, int signal);

#endif
