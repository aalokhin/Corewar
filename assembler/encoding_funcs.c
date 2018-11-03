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


void	fill_corfile_contents(t_binfile *bin)
{
	//******************************* filling magic *************************
	int i;

	i = 0;
	while(i < 4)
	{
		printf("writing ....\n");
		write(bin->fd_file_out, &bin->magic_start[i], 1);
		i++;
	}
	//******************************* filling fucking name *************************
	char 		*str;
	//printf("~~~~~~~~~~~~~~~okoko\n");
	str = ft_strstr(bin->f_contents, ".name");
	i = 0;
	int tmp = 0;

	while(str[i] != '"')
		i++;
	tmp = ++i;
	while(str[i] != '"')
		i++;
	bin->name = ft_strnew(PROG_NAME_LENGTH );
	ft_strncpy(bin->name, &str[tmp], i - tmp);
	printf("name of the champ is {%s} \n", bin->name);

	str = ft_strstr(bin->f_contents, ".comment");
	i = 0;
	tmp = 0;
	while(str[i] != '"')
		i++;
	tmp = ++i;
	while(str[i] != '"')
		i++;
	bin->comment = ft_strnew(COMMENT_LENGTH);
	
	ft_strncpy(bin->comment, &str[tmp], i - tmp);
	printf("comment is of the champ is {%s} \n", bin->comment);

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		//printf("writing name  ....\n");
		write(bin->fd_file_out, &bin->name[i], 1);
		i++;
	}
	write(bin->fd_file_out, "\0\0\0\0", 4);
	write(bin->fd_file_out, "\0\0\0\0", 4);
	//write(bin->fd_file_out, "a", 2);

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		//printf("i am here \n");
		//printf("writing comment  ....\n");
		write(bin->fd_file_out, &bin->comment[i], 1);
		i++;

	}



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
// 	printf("die NAME =====> %s\n", c.name);
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