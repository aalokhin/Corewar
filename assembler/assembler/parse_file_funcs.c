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
	while ((*count) < bin->arg_length)
	{
		(*contents)[(*count)] = '\0';
		(*count)++;
	}
}




void		clean_name_comment(t_binfile *bin, char (*contents)[])
{
	size_t		i;
	size_t		len;
	size_t		k;
	
	i = 0;
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
}



void		clean_spaces(t_binfile *bin, char (*contents)[])
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while ((*contents)[i])
	{
		while ((*contents)[i] != '\n' && WHITESPACE((*contents)[i]))
			++i;
		if (j > 0 && (*contents)[j - 1] != '\n' && i > 0 && WHITESPACE((*contents)[i - 1]))
		{
			(*contents)[j] = ' ';
			j++;
		}
		if ((*contents)[i] && ((*contents)[i] == '\n' || !WHITESPACE((*contents)[i])))
		{
			ft_memmove(&(*contents)[j], &(*contents)[i], 1);
			j++;
			
		}
		i++;
	}
	ft_zero_what_left(bin, &j, contents);
	i = 0;
	while ((*contents)[i])
	{
		if ((*contents)[i] == ',')
			(*contents)[i] = ' ';
		i++;
	}

}


void			clean_new_lines(t_binfile *bin, char (*contents)[])
{
	size_t		j;
	size_t		i;
	size_t		len;

	j = 0;
	i = 0;
	len = 0;
	



	while((*contents)[i])
	{
	
		if ((*contents)[i] == '\n')
			while ((*contents)[i + 1] == '\n')
				++i;
		// if (!(*contents)[i])
		// 	return ;
		ft_memmove(&(*contents)[j], &(*contents)[i], 1);
		j++;
		i++;

	}
	ft_zero_what_left(bin, &j, contents);


}



void 		parse_file(t_binfile *bin, char (*contents)[]) //cleaning from  comments and extra lines
{
	size_t		i;

	size_t		len;
	size_t		k;

	k = 0;

	
	len = 0;

	i = 0;
	
	//printf("here\n");
	//skip_name_comment(&i, contents);

	k = 0;
	while (i < bin->arg_length)//(i < bin->arg_length)
	{
		if ((*contents)[i] == '#' || (*contents)[i] == ';')
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
	clean_name_comment(bin, contents);
	ft_zero_what_left(bin, &k, contents);

	clean_spaces(bin, contents);
	//ft_skip_nl(contents, (int)bin->arg_length);
	clean_new_lines(bin, contents);


	
}