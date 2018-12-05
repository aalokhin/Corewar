/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bots_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:26:24 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/16 15:26:26 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		if_correct_name(unsigned char *str, t_flags *params, int j)
{
	int i;

	i = MAGIC_S;
	while (i < PROG_NAME_L + MAGIC_S)
		i++;
	while (i < PROG_NAME_L + MAGIC_S + NULL_S)
	{
		if (str[i] != 0)
		{
			ft_printf("Error: File %s has an invalid header\n",
				(*params).players[j]);
			return (0);
		}
		i++;
	}
	while (i < PROG_NAME_L + MAGIC_S + NULL_S + EXEC_S + COMMENT_L)
		i++;
	while (i < PROG_NAME_L + MAGIC_S + NULL_S * 2 + EXEC_S + COMMENT_L)
	{
		if (str[i] != 0)
		{
			ft_printf("Error: File %s has an invalid header\n",
				(*params).players[j]);
			return (0);
		}
		i++;
	}
	return (1);
}

int		check_magic(unsigned char *str, t_flags *params, int j,
	t_header bots[MAX_PLAYERS])
{
	unsigned int	magic;
	unsigned int	buf;

	magic = 0;
	buf = 0;
	buf = str[0] << 24;
	magic |= buf;
	buf = str[1] << 16;
	magic |= buf;
	buf = str[2] << 8;
	magic |= buf;
	magic |= str[3];
	bots[j].magic = magic;
	if (magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("Error: File %s has an invalid header\n",
		(*params).players[j]);
		return (0);
	}
	return (1);
}

int		check_comment(unsigned char *str, t_flags *params, int j)
{
	int		i;

	i = 140;
	while (str[i] && i < PRE_EXEC_S - NULL_S)
		i++;
	if (i == PRE_EXEC_S - NULL_S)
	{
		ft_printf("Error: File %s has an invalid header\n",
		(*params).players[j]);
		return (0);
	}
	return (1);
}
