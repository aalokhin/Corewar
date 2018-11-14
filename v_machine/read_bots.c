/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bots.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:58:08 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/14 15:58:11 by vlikhotk         ###   ########.fr       */
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
		ft_printf("Error: File %s has an invalid header\n", (*params).players[j]);
		return (0);
	}
	while (i < 133)
	{
		if (str[i] != '\0')
		{
			ft_printf("Error: File %s has an invalid header\n", (*params).players[j]);
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
		ft_printf("Error: File %s has an invalid header\n", (*params).players[j]);
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
		ft_printf("Error: File %s has an invalid header\n", (*params).players[j]);
		return (0);
	}
	return (1);
}

int		take_bots_params(unsigned char *str, t_flags *params, int j,
	header_t bots[4])
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

int	copy_bots_to_map(header_t bots[4], int j, unsigned char *str,
	t_flags *params)
{
	unsigned int i;

	i = 0;
	ft_bzero(bots[j].exec_part, bots[j].prog_size + 1);
	bots[j].start_index = (MEM_SIZE / (*params).bots_quantity) * j;
	while (i < bots[j].prog_size)
	{
		bots[j].exec_part[i] = str[2192 + i];
		i++;
	}
	ft_strdel((char **)(&str));
	return (1);
}

int		read_bots(t_flags *params, int fd, header_t bots[4])
{
	int				j;
	unsigned int	len;
	unsigned char	*str;

	j = 0;
	while ((*params).players[j] != NULL)
	{
		if ((fd = open((*params).players[j], O_RDONLY)) < 0)
		{
			ft_printf("%s %s\n", "Can't read source file",
				(*params).players[j]);
			return (0);
		}
		len = (int)lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);
		str = (unsigned char *)malloc(sizeof(unsigned char) * len + 1);
		read(fd, str, len);
		if (!check_magic(str, params, j, bots) || !if_correct_name(str, params, j) ||
			!check_comment(str, params, j))
			return (0);
		ft_strncpy(bots[j].prog_name, (const char *)(&str[4]),
			PROG_NAME_LENGTH);
		if (!take_bots_params(str, params, j, bots) ||
			!copy_bots_to_map(bots, j, str, params))
			return (0);
		if (len - 2192 != bots[j].prog_size)
		{
			ft_printf("Error: File %s has a code size that differ from what its header says\n",
				(*params).players[j]);
			return (0);
		}
		j++;
	}
	return (1);
}
