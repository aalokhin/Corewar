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

int		check_if_norepeat_id(t_flags *params, int id_to_check, int if_start)
{
	int i;
	int id_to_check_tmp;

	i = 0;
	id_to_check_tmp = 0;
	while (i < MAX_PLAYERS)
	{
		if (if_start)
			id_to_check_tmp = (*params).pl_nbr[i][1];
		else
			id_to_check_tmp = (*params).pl_nbr[i][1] - 1;
		if ((*params).pl_nbr[i][0] && id_to_check == id_to_check_tmp)
			return (1);
		i++;
	}
	return (0);
}

int		if_correct_name(unsigned char *str, t_flags *params, int j)
{
	(*params).i = MAGIC_S;
	while ((*params).i < PROG_NAME_L + MAGIC_S)
		(*params).i++;
	while ((*params).i < PROG_NAME_L + MAGIC_S + NULL_S)
	{
		if (str[(*params).i++] != 0)
		{
			ft_printf("Error: File %s has an invalid header\n",
				(*params).players[j]);
			return (0);
		}
	}
	while ((*params).i < PROG_NAME_L + MAGIC_S + NULL_S + EXEC_S + COMMENT_L)
		(*params).i++;
	while ((*params).i < PROG_NAME_L + MAGIC_S + NULL_S * 2
		+ EXEC_S + COMMENT_L)
	{
		if (str[(*params).i++] != 0)
		{
			ft_printf("Error: File %s has an invalid header\n",
				(*params).players[j]);
			return (0);
		}
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

	i = PROG_NAME_L + MAGIC_S + NULL_S + EXEC_S;
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
