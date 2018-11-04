#include "asm.h"

void		skip_name_comment(size_t	*count,  char (*contents)[])
{
	size_t 		k;

	k = 0;
	while(k != 4)
	{
		if ((*contents)[(*count)] == '"')
			k++;
		(*count)++;
	}
	while ((*contents)[(*count)] && (*contents)[(*count)] != '\n')
		(*count)++;
}

void		ft_zero_what_left(t_binfile *bin, size_t	*count,  char (*contents)[])
{
	//printf("\n\n\nhere\n\n\n\n\n");
	while ((*count) < bin->arg_length)
	{
		(*contents)[(*count)] = '\0';
		(*count)++;
	}
}


void 		parse_file(t_binfile *bin, char (*contents)[])
{
	size_t		i;
	size_t		j;
	size_t		len;
	size_t		k;

	k = 0;

	
	len = 0;
	j = 0;

	i = 0;
	
	//printf("here\n");
	//skip_name_comment(&i, contents);

	k = 0;
	while (i < bin->arg_length)//(i < bin->arg_length)
	{
		if ((*contents)[i] == '#')
		{
			len = 0;
			//printf("1==>%c<==1\n", (*contents)[i]);
			while((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);
	//printf("{%s}", *contents);



	i = 0;
	
	//printf("here\n");
	//skip_name_comment(&i, contents);

	k = 0;
	len = 0;
	while (i < bin->arg_length)//(i < bin->arg_length)
	{

		if (ft_strncmp(&(*contents)[i], ".name", 5) == 0 ||\
			ft_strncmp(&(*contents)[i], ".comment", 8) == 0)
		{
			len = 0;
			//printf("1==>%c<==1\n", (*contents)[i]);
			while((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);

	//skip_name_comment(&i, contents);
	// printf("yooo [[%lu]]", k);
	// printf("[%s]<+=======\n", contents);
}

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