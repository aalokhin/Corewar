#include "asm.h"
	
void	label_distance(t_binfile 	*bin)
{
	bin->arg_length = bin->arg_length;
	bin->champ_size_nbr = 0;


	t_lable *tmp;
	t_t		*tmpi;	

	tmp = bin->labels_list;


	tmp = bin->labels_list;
	while(tmp)
	{
		if (!tmp->prev)
			tmp->bytes_above = 0;
		else
			tmp->bytes_above = tmp->prev->lbl_len + 1;
		tmp = tmp->next;
	}

	tmp = bin->labels_list;
	while(tmp)
	{

		
		tmpi = tmp->instruct;
		printf("label of %d name is: %s with %d bytes_above)\n", tmp->lbl_len, tmp->label_name, tmp->bytes_above);
		//printf(" label name is \"%s\" - ",  tmp->label_name);
		// if (tmp->prev)
		// 	printf("label<-prev \"%s\" -", tmp->prev->label_name);
		// else
		// 	printf("no prev\n");
		// if (tmp->next)
		// 	printf("label->next \"%s\" \n", tmp->next->label_name);
		// else
		// 	printf("no next\n");

		while(tmpi)
		{
			bin->champ_size_nbr += tmpi->c_len;
			printf("		=>instruction is: %s and it's size  %d\n", tmpi->name_c, tmpi->c_len);
			tmpi = tmpi->next;
		}
		tmp = tmp->next;
	}
	printf("executable code length: %x\n", bin->champ_size_nbr);
}
