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

	i = 4;
	while (str[i] && i < 133)
		i++;
	if (i == 133)
	{
		ft_printf("Error: File %s has an invalid header\n",
			(*params).players[j]);
		return (0);
	}
	while (i < 133)
	{
		if (str[i] != '\0')
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
	header_t bots[4])
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
	while (str[i] && i < 2188)
		i++;
	if (i == 2188)
	{
		ft_printf("Error: File %s has an invalid header\n",
		(*params).players[j]);
		return (0);
	}
	return (1);
}
