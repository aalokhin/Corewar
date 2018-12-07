/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdynia <mdynia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:04:24 by mdynia            #+#    #+#             */
/*   Updated: 2018/12/06 16:04:25 by mdynia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		no_name_comment(t_binfile *file, char **str_n, char **comma)
{
	char **str;

	str = NULL;
	if (!file->name || !file->comment)
	{
		str = ft_strsplit(str_n[0], ' ');
		error_message(file, str[0], define_line_num(file->copy, str[0], 0, 0));
		return (clean(str, str_n, comma));
	}
	return (1);
}

int		label_filler(t_binfile *file, t_lable **label, char **str, int *i)
{
	if (*label)
		*label = labels_linker(file, *label);
	*label = (t_lable *)ft_memalloc(sizeof(t_lable));
	if (!(label_name_is_valid(file, *label, str[*i])))
	{
		labels_linker(file, *label);
		return (0);
	}
	*i += 1;
	return (1);
}

int		my_end(t_binfile *file, t_lable *label, char **str_n, char **comma)
{
	if (label)
		labels_linker(file, label);
	ft_clean_parse(str_n);
	ft_clean_parse(comma);
	file_length(file);
	return (1);
}

int		cmd_linker_add(t_binfile *file, t_lable *label, t_t *token)
{
	command_linker(label, token);
	labels_linker(file, label);
	return (1);
}
