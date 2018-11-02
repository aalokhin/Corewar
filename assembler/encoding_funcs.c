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
	bin->name = ft_strnew(i - tmp);
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
	bin->comment = ft_strnew(i - tmp);
	ft_strncpy(bin->comment, &str[tmp], i - tmp);
	printf("comment is of the champ is {%s} \n", bin->comment);

	i = 0;
	while (i <= PROG_NAME_LENGTH)
	{
		printf("writing name  ....\n");
		write(bin->fd_file_out, &bin->name[i], 1);
		i++;

	}



}


/* ************************************************************************** */

// #include "includes/libft.h"

// char	*ft_strstr(const char *big, const char *little)
// {
// 	int i;
// 	int j;
// 	int res;

// 	i = 0;
// 	if (little[i] == 0)
// 		return (char *)(big);
// 	while (big[i] != 0)
// 	{
// 		res = i;
// 		j = 0;
// 		while (big[i + j] == little[j] && little[j] != 0 && big[i + j] != 0)
// 			j++;
// 		if (little[j] == 0)
// 			return (char *)(&big[res]);
// 		else
// 			i++;
// 	}
// 	return (NULL);
// }

