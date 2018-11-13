#include "asm.h"

int 		find_arg_value(t_binfile *bin, char *str, t_t *instruct, t_lable *label)
{
	char 		*search;
	t_lable		*tmp_lbl;

	tmp_lbl = bin->labels_list;
	if (ft_strstr(str, "%:"))
	{
		search = ft_strstr(str, "%:") + 2;
		while(tmp_lbl)
		{
			if (tmp_lbl->label_name)
			{
				if (strcmp(search, tmp_lbl->label_name) == 0)
				{
					if (label->bytes_above < tmp_lbl->bytes_above)
						return (tmp_lbl->bytes_above - label->bytes_above - instruct->bytes_above_i);
					else
						return (tmp_lbl->bytes_above - (label->bytes_above +  instruct->bytes_above_i));
				}
			}
			tmp_lbl = tmp_lbl->next;
		}
		
	}
	return (ft_strstr(str, "r") ? ft_atoi(ft_strstr(str, "r") + 1) : ft_strstr(str, "%")  ? ft_atoi(ft_strstr(str, "%") + 1) : ft_atoi(str));
}

void	label_distance(t_binfile 	*bin)
{
	int k;
	t_lable *tmp;
	t_t		*tmpi;	

	tmp = bin->labels_list;
	while(tmp)
	{
	
		tmpi = tmp->instruct;
		//printf(" === label  name is: {%s} with %d bytes_above) ===\n", tmp->label_name, tmp->bytes_above);
		k = 0;
		while(tmpi)
		{
			k = 0;
			//printf("	=>instruction  is: %s (opcode %d) and it's size  %d\n", tmpi->name_c, tmpi->opcode,  tmpi->c_len);
			// printf("				args: ");
			while(tmpi->a[k])
			{
				tmpi->args[k][1] = find_arg_value(bin, tmpi->a[k], tmpi, tmp);
				k++;
			}
			tmpi = tmpi->next;
			//printf("\n");
		}
		tmp = tmp->next;
	}
}
