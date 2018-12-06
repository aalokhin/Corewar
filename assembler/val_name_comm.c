/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_name_comm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:24:57 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/06 16:25:02 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				count_bracks(char *str)
{
	size_t			i;
	size_t			d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if (str[i] == '"')
			d++;
		i++;
	}
	if (d != 4)
		return (0);
	return (1);
}

int				check_com(char *comm, int i, int j)
{
	char		*str;

	str = ft_strstr(comm, COMMENT_CMD_STRING);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			j++;
		i++;
	}
	if (j != 2)
		return (0);
	return (1);
}

int				val_n_c(char *file, int i, int j)
{
	char		*str;
	char		*str2;

	j = 0;
	if (!file || !(ft_strstr(file, NAME_CMD_STRING) &&\
	ft_strstr(file, COMMENT_CMD_STRING) && count_bracks(file)))
		return (0);
	str = ft_strstr(file, NAME_CMD_STRING);
	str2 = ft_strstr(file, COMMENT_CMD_STRING);
	if (str > str2)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			j++;
		if (ft_strstr(&str[i], COMMENT_CMD_STRING) && j >= 2)
			break ;
		i++;
	}
	if (j != 2 || !(ft_strstr(&str[i], COMMENT_CMD_STRING))\
	|| !check_com(&str[i], 0, 0))
		return (0);
	return (1);
}
