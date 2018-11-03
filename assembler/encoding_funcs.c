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
	printf("stirng of length %d :  %s\n", len, bin->arg_name);
	corfile = ft_strnew(len + 3);
	if (!corfile)
		return ;
	ft_strncpy(corfile, bin->arg_name, len - 1);
	ft_strcpy(&corfile[len - 1], "cor");

	printf("stirng 2 %s\n", corfile);
	bin->fd_file_out = open(corfile, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	ft_strdel(&corfile);
	fill_corfile_contents(bin);

}

