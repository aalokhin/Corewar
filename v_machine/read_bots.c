/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bots.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:58:08 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/12/03 18:54:31 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		check_bot_size(int len, unsigned char *str, t_header bots[MAX_PLAYERS],
	t_flags *params)
{
	if ((unsigned int)(len - PRE_EXEC_S) != bots[(*params).j].prog_size)
	{
		ft_printf("%s %s %s\n", "Error: File", (*params).players[(*params).j],
		"has a code size that differ from what its header says");
		ft_strdel((char **)(&str));
		return (0);
	}
	if (bots[(*params).j].prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n",
		(*params).players[(*params).j],
		bots[(*params).j].prog_size, CHAMP_MAX_SIZE);
		ft_strdel((char **)(&str));
		return (0);
	}
	if ((*params).sum_bots > MEM_SIZE)
	{
		ft_printf("Error: %s %d MEM_SIZE for this game\n",
		"Too small map size, you need at least",
		(*params).sum_bots);
		return (0);
	}
	return (1);
}

int		take_bots_params(unsigned char *str, t_flags *params, int len,
	t_header bots[MAX_PLAYERS])
{
	unsigned int size;
	unsigned int buf;

	size = 0;
	buf = 0;
	buf = str[136] << 24;
	size |= buf;
	buf = str[137] << 16;
	size |= buf;
	buf = str[138] << 8;
	size |= buf;
	size |= str[139];
	bots[(*params).j].prog_size = size;
	(*params).sum_bots += size;
	if (!check_bot_size(len, str, bots, params))
		return (0);
	ft_strncpy(bots[(*params).j].comment,
		(const char *)(&str[PROG_NAME_L + MAGIC_S + NULL_S + EXEC_S]),
		COMMENT_L);
	bots[(*params).j].exec_part = (unsigned char *)malloc(sizeof(unsigned char)
	* (bots[(*params).j].prog_size));
	return (1);
}

int		copy_bots_to_map(t_header bots[MAX_PLAYERS], unsigned char *str,
	t_flags *params)
{
	(*params).i = 0;
	ft_bzero(bots[(*params).j].exec_part, bots[(*params).j].prog_size);
	bots[(*params).j].start_index = (MEM_SIZE /
	(*params).bots_quantity) * (*params).j;
	while ((unsigned int)(*params).i < bots[(*params).j].prog_size)
	{
		bots[(*params).j].exec_part[(*params).i] =
		str[PRE_EXEC_S + (*params).i];
		(*params).i++;
	}
	ft_strdel((char **)(&str));
	(*params).j++;
	return (1);
}

int		bot_open(int *fd, t_flags *params, unsigned int *len)
{
	if ((*fd = open((*params).players[(*params).j], O_RDONLY)) < 0)
	{
		ft_printf("%s %s\n", "Error: Incorrect arg or can't read source file",
			(*params).players[(*params).j]);
		return (0);
	}
	*len = (int)lseek(*fd, 0, SEEK_END);
	if (*len < PRE_EXEC_S)
	{
		ft_printf("Error: File %s is too small to be a champion\n",
			(*params).players[(*params).j]);
		return (0);
	}
	lseek(*fd, 0, SEEK_SET);
	return (1);
}

int		read_bots(t_flags *params, int fd, t_header bots[MAX_PLAYERS])
{
	unsigned int			len;
	static unsigned char	*str;

	while ((*params).j < (*params).bots_quantity)
	{
		if (!bot_open(&fd, params, &len))
			return (0);
		str = (unsigned char *)malloc(sizeof(unsigned char) * len + 1);
		str[len] = '\0';
		read(fd, str, len);
		if (!take_bots_params(str, params, len, bots) ||
		!check_magic(str, params, (*params).j, bots) ||
		!if_correct_name(str, params, (*params).j) ||
		!check_comment(str, params, (*params).j))
			return (0);
		ft_strncpy(bots[(*params).j].prog_name,
		(const char *)(&str[MAGIC_S]), PROG_NAME_L);
		if (!copy_bots_to_map(bots, str, params))
			return (0);
		close(fd);
	}
	(*params).i = 0;
	(*params).j = 0;
	create_map(bots, params);
	return (1);
}
