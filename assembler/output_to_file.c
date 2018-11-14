#include "asm.h"

void			print_four_bytes(unsigned int src, int fd_out)
{
	unsigned char	a[4];
	int 			i;

	i = 0; 
//	printf("LENGTH is %u\n", bin->file_length);
	a[3] = src & 255;
	a[2] = (src >> 8) & 255;
	a[1] = (src >> 16) & 255;
	a[0] = (src >> 24) & 255;
	while (i < 4)
	{
		write(fd_out, &a[i], 1);
		i++;
	}
}

void				print_reg_to_file(int i, t_t *tmp, int fd_out)
{
	unsigned char	a;

	a = tmp->args[i][1] & 0xFF;
	write(fd_out, &a, 1);
}

void				print_ind_to_file(int i, t_t *tmp, int fd_out)
{
	unsigned char	a[2];
	int				z;

	a[1] = tmp->args[i][1] & 0xFF;
	a[0] = (tmp->args[i][1] >> 8) & 0xFF;
	z =  0;
	while(z < 2)
	{
		write(fd_out, &a[z], 1);
		z++;
	}
}

void				print_dir_to_file(int i, t_t *tmp, int fd_out)
{
	if (tmp->lbl_size == 4)
		print_four_bytes((unsigned int)tmp->args[i][1], fd_out);
	else
		print_ind_to_file(i, tmp, fd_out);
}

void				print_exec_to_file(t_binfile *bin, size_t i)
{
	unsigned char a[4];
	t_lable *lable;
	t_t *tmp;

	lable = bin->labels_list;
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
			while(i < (size_t)tmp->arguments)
			{
				if (tmp->args[i][0] == 10)
					print_dir_to_file(i, tmp, bin->fd_file_out);
				else if (tmp->args[i][0] == 11)
					print_ind_to_file(i, tmp, bin->fd_file_out);
				else if (tmp->args[i][0] == 1)
					print_reg_to_file(i, tmp, bin->fd_file_out);
				i++;
			}
			tmp = tmp->next;
		}
		lable = lable->next;
	}
}


void	fill_corfile_contents(t_binfile *bin)
{
	size_t i;
	t_lable *lable;

	lable = bin->labels_list;
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
	print_four_bytes(bin->file_length, bin->fd_file_out);

	//******************************* filling comment *************************

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		write(bin->fd_file_out, &bin->comment[i], 1);
		i++;

	}
	write(bin->fd_file_out, "\0\0\0\0", 4);

//******************************* filling exec part *************************
	
	print_exec_to_file(bin, 0);
	ft_print_success(bin);
}