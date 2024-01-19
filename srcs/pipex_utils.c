/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:13:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/19 14:09:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_cmd	*pipex_lstnew(char *args)
{
	t_cmd	*cmd;

	if (!args)
		return (0);
	cmd = (t_cmd *) ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (cmd);
	cmd -> flags = ft_split(args, ' ');
	cmd -> bin = *(cmd)-> flags;
	cmd -> next = 0;
	return (cmd);
}

static t_cmd	*pipex_lstlast(t_cmd *cmds)
{
	if (!cmds)
		return (0);
	while (cmds -> next)
		cmds = cmds -> next;
	return (cmds);
}

void	pipex_lstadd_back(t_cmd **cmds, char *args)
{
	if (!cmds || !args)
		return ;
	if (!(*cmds))
		*cmds = pipex_lstnew(args);
	else
		pipex_lstlast(*cmds)-> next = pipex_lstnew(args);
}

void	pipex_lstclear(t_cmd **cmds)
{
	int		i;
	t_cmd	*tmp;

	if (!cmds)
		return ;
	while (*cmds)
	{
		tmp = *cmds;
		i = 0;
		while (*(tmp -> flags + i))
			free(*(tmp -> flags + i++));
		free(tmp -> flags);
		*cmds = (*cmds)-> next;
		free(tmp);
	}
}
