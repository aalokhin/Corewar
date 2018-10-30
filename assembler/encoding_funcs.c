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
	char	*new_name;

	new_name = ft_strdup(bin->arg_name);
	new_name[ft_strlen(new_name) - 1] = 'f'; //fix this im doing something wrong
	bin->fd_file_out = open(new_name, O_CREAT|O_WRONLY|O_TRUNC);

}

// void	ft_print_cr(t_cor c, char *argv, int exec_len)
// {
// 	int		fd;
// 	int		l;
// 	char	*file;

// 	ft_name(c.f_n, &(c.name), PROG_NAME_LENGTH);
// 	ft_name(c.f_c, &(c.comment), COMMENT_LENGTH);
// 	file = ft_out(argv);
// 	if (!file)
// 		return ;
// 	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
// 	ft_strdel(&file);
// 	l = 4;
// 	ft_print_cor(c.magic, l, fd);
// 	l = PROG_NAME_LENGTH;
// 	ft_print_cor(c.name, l, fd);
// 	l = 4;
// 	ft_print_cor("\0\0\0\0", l, fd);
// 	ft_print_cor(c.exec_size, l, fd);
// 	l = COMMENT_LENGTH;
// 	ft_print_cor(c.comment, l, fd);
// 	l = 4;
// 	ft_print_cor("\0\0\0\0", l, fd);
// 	l = exec_len;
// 	ft_print_cor(c.exec, l, fd);
// 	close(fd);
// }

