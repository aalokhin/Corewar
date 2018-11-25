#include "asm.h"

int			find_arg_value(t_binfile *bin, char *str, t_t *instruct, t_lable *label)
{
	char	*search;
	t_lable	*tmp_lbl;

	tmp_lbl = bin->labels_list;
	if (ft_strstr(str, "%:"))
	{
		search = (char *)ft_memalloc(sizeof(char) * ft_strlen(str));
		search = ft_strstr(str, "%:") + 2;
		search = ft_strjoin(search, ":");
		while (tmp_lbl)
		{
			if (tmp_lbl->label_name)
			{
				if (strcmp(search, tmp_lbl->label_name) == 0)
				{
					ft_strdel(&search);
					if (label->bytes_above < tmp_lbl->bytes_above)
						return (tmp_lbl->bytes_above - label->bytes_above - instruct->bytes_above_i);
					else
						return (tmp_lbl->bytes_above - (label->bytes_above + instruct->bytes_above_i));
				}
			}
			tmp_lbl = tmp_lbl->next;
		}
		ft_strdel(&search);
	}
	if (ft_strstr(str, "r"))
		return (ft_atoi(ft_strstr(str, "r") + 1));
	else if (ft_strstr(str, "%"))
		return (ft_atoi(ft_strstr(str, "%") + 1));
	else
		return (ft_atoi(str));
}

int					label_distance(t_binfile *bin)
{
	int					k;
	t_lable				*tmp;
	t_t					*tmpi;

	tmp = bin->labels_list;
	while (tmp)
	{
		tmpi = tmp->instruct;
		k = 0;
		while (tmpi)
		{
			k = 0;
			while (tmpi->a[k])
			{
				tmpi->args[k][1] = find_arg_value(bin, tmpi->a[k], tmpi, tmp);
				//ft_strdel(&(tmpi->a[k])); // we need this in flag i 
				k++;
			}
			tmpi = tmpi->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

