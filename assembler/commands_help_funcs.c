/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_help_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:32:19 by aalokhin          #+#    #+#             */
/*   Updated: 2018/11/30 16:32:25 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_cmd_lbls(char *c_name)
{
	const char		lbls2[6][6] = {"zjmp", "ldi", "sti",\
	"fork", "lldi", "lfork"};
	const char		lbls4[10][6] = {"live", "ld", "st",\
	"add", "sub", "and", "or", "xor", "lld", "aff"};
	int				i;

	if (!c_name)
		return (0);
	i = -1;
	while (++i < 6)
	{
		if (ft_strcmp(lbls2[i], c_name) == 0)
			return (2);
	}
	i = -1;
	while (++i < 10)
	{
		if (ft_strcmp(lbls4[i], c_name) == 0)
			return (4);
	}
	return (0);
}

void				clean_name_comment(t_binfile *bin, char (*contents)[])
{
	size_t			i;
	size_t			len;
	size_t			k;

	i = 0;
	k = 0;
	len = 0;
	while (i < bin->arg_length)
	{
		if (ft_strncmp(&(*contents)[i], ".name", 5) == 0 ||\
			ft_strncmp(&(*contents)[i], ".comment", 8) == 0)
		{
			move_name_comment(&(*contents), &i);
			len = 0;
			while ((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len + 1);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);
}

void				ft_clean_commas(char (*contents)[])
{
	size_t			i;

	i = 0;
	while ((*contents)[i])
	{
		if ((*contents)[i] == ',')
			(*contents)[i] = ' ';
		i++;
	}
}

void				clean_spaces(t_binfile *bin, char (*contents)[])
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while ((*contents)[i])
	{
		while ((*contents)[i] != '\n' && WHITESPACE((*contents)[i]))
			++i;
		if (j > 0 && (*contents)[j - 1] != '\n' && i > 0\
		&& WHITESPACE((*contents)[i - 1]))
		{
			(*contents)[j] = ' ';
			j++;
		}
		if ((*contents)[i] && ((*contents)[i] == '\n' ||\
		!WHITESPACE((*contents)[i])))
		{
			ft_memmove(&(*contents)[j], &(*contents)[i], 1);
			j++;
		}
		i++;
	}
	ft_zero_what_left(bin, &j, contents);
	ft_clean_commas(contents);
}

void				clean_new_lines(t_binfile *bin, char (*contents)[])
{
	size_t			j;
	size_t			i;
	size_t			len;

	j = 0;
	i = 0;
	len = 0;
	while ((*contents)[i])
	{
		if ((*contents)[i] == '\n')
		{
			while ((*contents)[i + 1] == '\n')
				++i;
			if ((*contents)[0] == '\n')
				i++;
		}
		ft_memmove(&(*contents)[j], &(*contents)[i], 1);
		j++;
		i++;
	}
	ft_zero_what_left(bin, &j, contents);
}
