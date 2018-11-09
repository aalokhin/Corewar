#include "asm.h"



void	fill_corfile_contents(t_binfile *bin)
{
	//******************************* filling magic *************************
	size_t i;
	t_lable *lable;
	t_t *tmp;

	lable = bin->labels_list;

	unsigned char a[4];

	i = 0;
	while(i < 4)
	{
		//printf("writing ....\n");
		write(bin->fd_file_out, &bin->magic_start[i], 1);
		i++;
	}
	//******************************* filling fucking name *************************
	

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		write(bin->fd_file_out, &bin->name[i], 1);
		i++;
	}
	write(bin->fd_file_out, "\0\0\0\0", 4);
	write(bin->fd_file_out, "\0\0\0\0", 4);

	i = 0;
	// printf("BIN_COMMENT:          %s\n",bin->comment );
	while (i < COMMENT_LENGTH)
	{
		// if (i <= 10)
		// 	printf("===444444=====>%c\n", bin->comment[i]);
		write(bin->fd_file_out, &bin->comment[i], 1);
		i++;

	}
	write(bin->fd_file_out, "\0\0\0\0", 4);

	i = 0;

	while(lable)
	{
		tmp = lable->instruct;
		while(tmp)
		{
			a[0] = tmp->opcode & 0x000000FF;
			a[1] = (tmp->opcode & 0x000000FF) >> 8;
			
			write (bin->fd_file_out, &a, 1);
			if (tmp->has_codage)
			{
				a[0] = tmp->codage & 0x000000FF;
				a[1] = (tmp->codage & 0x000000FF) >> 8;
				i = 0;
				write (bin->fd_file_out, &a, 1);
			}
			i = 0;
			while(i < (size_t)tmp->arguments)
			{
				write(bin->fd_file_out, &tmp->args[i][0], 1);
				//write(bin->fd_file_out, &tmp->args[i][1], 1);
				i++;
			}



			//printf("%x\n", tmp->opcode);
			tmp = tmp->next;
		}
		lable = lable->next;
	}


}