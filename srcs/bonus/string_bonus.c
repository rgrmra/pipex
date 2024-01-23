/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:53:03 by rde-mour          #+#    #+#             */
/*   Updated: 2024/01/22 19:11:12 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	find_double_quotte(char **str)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (*str && *(*(str) + i))
	{
		if (*(*(str) + i) == '\"' && c == '\a')
			c = ' ';
		else if (*(*(str) + i) == '\"' && c == ' ')
			c = '\a';
		if (*(*(str) + i) == ' ')
			*(*(str) + i) = c;
		else if (*(*(str) + i) == '\"')
			*(*(str) + i) = ' ';
		i++;
	}
}

static void	find_single_quotte(char **str)
{
	int		i;

	i = 0;
	while (*str && *(*(str) + i))
	{
		if ((*(*(str) + i) == '\'' && *(*(str) + i + 1) == ' ')
			|| (*(*(str) + i) == '\'' && *(*(str) + i + 1) == '\0')
			|| (i > 0 && *(*(str) + i - 1) == ' ' && *(*(str) + i) == '\'')
			|| (i == 0 && *(*(str) + i) == '\''))
			*(*(str) + i) = '\"';
		i++;
	}
	find_double_quotte(str);
}

void	ft_split_quotte(char *str, char ***splitted)
{
	int		i;

	find_double_quotte(&str);
	find_single_quotte(&str);
	*splitted = ft_split(str, ' ');
	i = 0;
	while (*(*(splitted) + i))
		ft_strrplc(*(*(splitted) + i++), '\a', ' ');
	free(str);
}
