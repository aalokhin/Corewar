/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:45:59 by aalokhin          #+#    #+#             */
/*   Updated: 2018/11/30 16:46:01 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				ft_zero_what_left(t_binfile *bin, size_t *c, char (*file)[])
{
	while ((*c) < bin->arg_length)
	{
		(*file)[(*c)] = '\0';
		(*c)++;
	}
}

void				move_name_comment(char (*contents)[], size_t *i)
{
	size_t d;

	d = 0;
	while ((*contents)[*i])
	{
		if ((*contents)[*i] == '"')
			d++;
		if (d == 2)
		{
			d = 0;
			break ;
		}
		(*i)++;
	}
}

void				remove_comments(t_binfile *bin, char (*contents)[])
{
	size_t			i;
	size_t			len;
	size_t			k;

	len = 0;
	i = 0;
	k = 0;
	while (i < bin->arg_length)
	{
		if ((*contents)[i] == COMMENT_CHAR || (*contents)[i] == ';')
		{
			len = 0;
			while ((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);
}

void				parse_file(t_binfile *bin, char (*contents)[])
{
	remove_comments(bin, contents);
	clean_name_comment(bin, contents);
	clean_spaces(bin, contents);
	clean_new_lines(bin, contents);
}
