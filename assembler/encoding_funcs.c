#include "asm.h"



void	fill_magic_start(t_binfile *bin)
{
	bin->magic_start[3] = (char)(COREWAR_EXEC_MAGIC & 255);
	bin->magic_start[2] = (char)((COREWAR_EXEC_MAGIC >> 8) & 255);
	bin->magic_start[1] = (char)((COREWAR_EXEC_MAGIC >> 16) & 255);
	bin->magic_start[0] = (char)((COREWAR_EXEC_MAGIC >> 24) & 255);

}



void	create_cor_file(t_binfile *bin)
{
	char			*corfile;
	unsigned int	len;

	len = ft_strlen(bin->arg_name);
	printf("stirng 1  %s\n", bin->arg_name);
	corfile = ft_memalloc(sizeof(len + 3)); //fix this im doing something wrong
	corfile[len + 3] = '\0';
	ft_strncpy(corfile, bin->arg_name, len - 1);
	ft_strcpy(&corfile[len - 1], "cor");
	printf("stirng 2 %s\n", corfile);
	bin->fd_file_out = open(corfile, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	ft_strdel(&corfile);
	fill_corfile_contents(bin);

}


void	fill_corfile_contents(t_binfile *bin)
{
	int i;

	i = 0;
	while(i < 4)
	{
		printf("writing .... %c\n", bin->magic_start[i]);
		write(bin->fd_file_out, &bin->magic_start[i], 1);
		i++;
	}

}
