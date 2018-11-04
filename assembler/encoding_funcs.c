#include "asm.h"



void	fill_magic_start(t_binfile *bin)
{
	bin->magic_start[3] = (char)(COREWAR_EXEC_MAGIC & 255);
	bin->magic_start[2] = (char)((COREWAR_EXEC_MAGIC >> 8) & 255);
	bin->magic_start[1] = (char)((COREWAR_EXEC_MAGIC >> 16) & 255);
	bin->magic_start[0] = (char)((COREWAR_EXEC_MAGIC >> 24) & 255);

}

void	fill_name_comment(t_binfile *bin)
{
	size_t i;

	i = 0;
	char 		*str;
	//printf("~~~~~~~~~~~~~~~okoko\n");
	str = ft_strstr(bin->f_contents, ".name");
	i = 0;
	size_t tmp = 0;

	while(str[i] != '"')
		i++;
	tmp = ++i;
	while(str[i] != '"')
		i++;
	bin->name = ft_strnew(PROG_NAME_LENGTH );
	ft_strncpy(bin->name, &str[tmp], i - tmp);
	//printf("name of the champ is {%s} \n", bin->name);

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
	//printf("\ncomment is of the champ is {%s} \n", bin->comment);
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
	
	//printf("[%s]\n", bin->f_contents);


	fill_corfile_contents(bin);
}

