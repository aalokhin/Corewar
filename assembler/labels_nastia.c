/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels_nastia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdynia <mdynia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 22:23:18 by mdynia            #+#    #+#             */
/*   Updated: 2018/12/05 22:23:19 by mdynia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			find_arg_value_help(t_lable *tmp, char *search, int inst, int label)
{
	while (tmp)
	{
		if (tmp->label_name)
		{
			if (strcmp(search, tmp->label_name) == 0)
			{
				ft_strdel(&search);
				if (label < tmp->bytes_above)
					return (tmp->bytes_above - label - inst);
				else
					return (tmp->bytes_above - (label + inst));
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int			find_arg_value(t_binfile *bin, char *str, t_t *c, t_lable *l)
{
	char	*search;
	char	*saved;
	t_lable	*tmp_lbl;

	tmp_lbl = bin->labels_list;
	if (ft_strstr(str, bin->z) || ft_strchr(str, LABEL_CHAR))
	{
		saved = ft_strstr(str, bin->z) ? ft_strstr(str, bin->z) + 2 :\
	ft_strchr(str, LABEL_CHAR) + 1;
		search = ft_strjoin(saved, bin->w);
		return (find_arg_value_help(tmp_lbl, search, c->bytes_above_i,\
			l->bytes_above));
	}
	if (ft_strstr(str, "r"))
		return (ft_atoi(ft_strstr(str, "r") + 1));
	else if (ft_strchr(str, DIRECT_CHAR))
		return (ft_atoi(ft_strchr(str, DIRECT_CHAR) + 1));
	else
		return (ft_atoi(str));
}

int			label_distance(t_binfile *bin)
{
	int		k;
	t_lable	*tmp;
	t_t		*ti;

	tmp = bin->labels_list;
	while (tmp)
	{
		ti = tmp->instruct;
		k = 0;
		while (ti)
		{
			k = 0;
			while (ti->a[k])
			{
				ti->args[k][1] = find_arg_value(bin, ti->a[k], ti, tmp);
				k++;
			}
			ti = ti->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
