#include "asm.h"



void	fill_corfile_contents(t_binfile *bin)
{
	//******************************* filling magic *************************
	size_t i;

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
	while (i < COMMENT_LENGTH)
	{
		write(bin->fd_file_out, &bin->comment[i], 1);
		i++;

	}
	write(bin->fd_file_out, "\0\0\0\0", 4);

}