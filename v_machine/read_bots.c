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

void	copy_bots_to_map(header_t bots[4], int j, unsigned char *str,
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
		ft_strncpy(bots[j].prog_name, (const char *)(&str[4]),
			PROG_NAME_LENGTH);
		if (!take_bots_params(str, params, j, bots))
			return (0);
		copy_bots_to_map(bots, j, str, params);
		j++;
	}
	return (1);
}
