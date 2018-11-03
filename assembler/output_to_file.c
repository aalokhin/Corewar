#include "asm.h"


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
