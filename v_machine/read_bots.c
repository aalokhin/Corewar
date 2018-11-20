/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bots.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:58:08 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/16 15:24:53 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		take_bots_params(unsigned char *str, t_flags *params, int j,
	t_header bots[4])
{
	unsigned int	size;
	unsigned int	buf;

	size = 0;
	buf = 0;
	buf = str[136] << 24;
	size |= buf;
	buf = str[137] << 16;
	size |= buf;
	buf = str[138] << 8;
	size |= buf;
	size |= str[139];
	bots[j].prog_size = size;
	if (size > 682)
	{
		ft_printf("Error: %s has too large a code (%d bytes > 682 bytes)\n",
			(*params).players[j], size);
		ft_strdel((char **)(&str));
		return (0);
	}
	ft_strncpy(bots[j].comment, (const char *)(&str[140]),
		COMMENT_LENGTH);
	bots[j].exec_part = (unsigned char *)malloc(sizeof(unsigned char) *
		(bots[j].prog_size + 1));
	return (1);
}

int		copy_bots_to_map(t_header bots[4], unsigned char *str,
	t_flags *params, int len)
{
	(*params).i = 0;
	ft_bzero(bots[(*params).j].exec_part, bots[(*params).j].prog_size + 1);
	bots[(*params).j].start_index = (MEM_SIZE /
	(*params).bots_quantity) * (*params).j;
	while ((unsigned int)(*params).i < bots[(*params).j].prog_size)
	{
		bots[(*params).j].exec_part[(*params).i] = str[2192 + (*params).i];
		(*params).i++;
	}
	ft_strdel((char **)(&str));
	if ((unsigned int)(len - 2192) != bots[(*params).j].prog_size)
	{
		ft_printf("%s %s %s\n", "Error: File", (*params).players[(*params).j],
		"has a code size that differ from what its header says");
		return (0);
	}
	return (1);
}

int		bot_open(int *fd, t_flags *params, unsigned int *len)
{
	if ((*fd = open((*params).players[(*params).j], O_RDONLY)) < 0)
	{
		ft_printf("%s %s\n", "Can't read source file",
			(*params).players[(*params).j]);
		return (0);
	}
	*len = (int)lseek(*fd, 0, SEEK_END);
	if (*len < 4 * 4 + PROG_NAME_LENGTH + COMMENT_LENGTH)
	{
		ft_printf("Error: File %s is too small to be a champion\n",
			(*params).players[(*params).j]);
		return (0);
	}
	lseek(*fd, 0, SEEK_SET);
	return (1);
}

int		read_bots(t_flags *params, int fd, t_header bots[4])
{
	unsigned int			len;
	static unsigned char	*str;

	(*params).j = 0;
	while ((*params).players[(*params).j] != NULL)
	{
		if (!bot_open(&fd, params, &len))
			return (0);
		str = (unsigned char *)malloc(sizeof(unsigned char) * len + 1);
		read(fd, str, len);
		if (!check_magic(str, params, (*params).j, bots) ||
		!if_correct_name(str, params, (*params).j) ||
		!check_comment(str, params, (*params).j))
			return (0);
		ft_strncpy(bots[(*params).j].prog_name, (const char *)(&str[4]),
			PROG_NAME_LENGTH);
		if (!take_bots_params(str, params, (*params).j, bots) ||
			!copy_bots_to_map(bots, str, params, len))
			return (0);
		close(fd);
		(*params).j++;
	}
	(*params).i = 0;
	(*params).j = 0;
	return (1);
}
