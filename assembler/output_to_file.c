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

//******************************* filling botsize *************************

	i = 0; 

	a[3] = bin->file_length & 255;
	a[2] = (bin->file_length >> 8) & 255;
	a[1] = (bin->file_length >> 16) & 255;
	a[0] = (bin->file_length >> 24) & 255;
	while (i < 4)
	{
		write(bin->fd_file_out, &a[i], 1);
		i++;
	}
	
	
	//******************************* filling comment *************************

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		write(bin->fd_file_out, &bin->comment[i], 1);
		i++;

	}
	write(bin->fd_file_out, "\0\0\0\0", 4);

//******************************* filling exec part *************************
	
	i = 0;
	int z = 0;

	while(lable)
	{
		tmp = lable->instruct;
		while(tmp)
		{
			a[0] = tmp->opcode & 0xFF;
			
			write (bin->fd_file_out, &a, 1);
			if (tmp->has_codage)
			{
				a[0] = tmp->codage & 0xFF;
				write (bin->fd_file_out, &a, 1);
			}
			i = 0;
			printf("arguments in instruction [%d]: \n",  tmp->arguments);

			while(i < (size_t)tmp->arguments)
			{
				printf("writing arg:   %d\n", tmp->args[i][0]);
				printf("writing arg_value:   %d\n", tmp->args[i][1]);


				if (tmp->args[i][0] == 10)
				{
					if (tmp->lbl_size == 4)
					{
						// a[0] = tmp->args[i][1] & 0x000000FF;
						// a[1] = (tmp->args[i][1] & 0x0000FF00) >> 8;
						// a[2] = (tmp->args[i][1] & 0x00FF0000) >> 16;
						// a[3] = (tmp->args[i][1] & 0xFF000000) >> 24;
						// z =  0;
						// while(z < 4)
						// {
						// 	write(bin->fd_file_out, &a[z], 1);
						// 	z++;
						// }
						a[3] = tmp->args[i][1] & 0x000000FF;
						a[2] = (tmp->args[i][1] & 0x0000FF00) >> 8;
						a[1] = (tmp->args[i][1] & 0x00FF0000) >> 16;
						a[0] = (tmp->args[i][1] & 0xFF000000) >> 24;
						z =  0;
						while(z < 4)
						{
							write(bin->fd_file_out, &a[z], 1);
							z++;
						}
					}
					else // == 2
					{
						// a[0] = tmp->args[i][1] & 0xFF;
						// a[1] = (tmp->args[i][1] >> 8) & 0xFF;
						// z =  0;
						// while(z < 2)
						// {
						// 	write(bin->fd_file_out, &a[z], 1);
						// 	z++;
						// }


						a[1] = tmp->args[i][1] & 0xFF;
						a[0] = (tmp->args[i][1] >> 8) & 0xFF;
						z =  0;
						while(z < 2)
						{
							write(bin->fd_file_out, &a[z], 1);
							z++;
						}
					}
					
				}
				else if (tmp->args[i][0] == 11)
				{
					// a[0] = tmp->args[i][1] & 0xFF;
					// a[1] = (tmp->args[i][1] >> 8) & 0xFF;
					// z =  0;
					// while(z < 2)
					// {
					// 	write(bin->fd_file_out, &a[z], 1);
					// 	z++;
					// }

					a[1] = tmp->args[i][1] & 0xFF;
					a[0] = (tmp->args[i][1] >> 8) & 0xFF;
					z =  0;
					while(z < 2)
					{
						write(bin->fd_file_out, &a[z], 1);
						z++;
					}
				}
				else if (tmp->args[i][0] == 1)
				{
					a[0] = tmp->args[i][1] & 0xFF;
					write(bin->fd_file_out, &a[0], 1);
				}
				

				i++;
			}



			//printf("%x\n", tmp->opcode);
			tmp = tmp->next;
		}
		lable = lable->next;
	}


}