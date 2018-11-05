#include "asm.h"


void		init_bin(t_binfile	*bin)
{
	(*bin).fd = 0;
	(*bin).flag_a = 0;

	(*bin).arg_length = 0;

	(*bin).champ_size_nbr = 0;

	(*bin).fd_file_out = 0;
	(*bin).arg_name = NULL;
	(*bin).f_contents = NULL;


	// printf(" ================>[%s]\n", bin->magic_start);

}

void 	print_struct(t_binfile	*bin)
{

	// 	start_color();
	// init_pair(1 , COLOR_GREEN, COLOR_BLACK);
	// attron(COLOR_PAIR(11));
	// printf("\nbin.arg_name ====>%s\n", bin->arg_name);
	// printf("bin.fd ====>%d\n", bin->fd);
	// printf("arg length ====>%u\n\n", bin->arg_length);
	//attroff( COLOR_PAIR(11));
	// printf("~~~~~~~~~~~~~~~~~~~~~~~~~~MAGIC\n");
	
	// printf("%x\n", 	(*bin).magic_start[3]);
	// printf("%x\n", (*bin).magic_start[2]);
	// printf("%x\n", (*bin).magic_start[1]);
	// printf("%x\n", (*bin).magic_start[0]);
	printf(" =>>>> [%s]\n", bin->f_contents);

}


int	 	ft_opening_file(t_binfile	*bin)
{
 	char file_contents[(*bin).arg_length + 1];
 	read((*bin).fd, file_contents, (*bin).arg_length);
 	file_contents[(*bin).arg_length] = '\0';
 	(*bin).f_contents = ft_strdup(file_contents);
 	parse_file(&(*bin), &file_contents);
 	//ft_space(&file_contents, (int)bin->arg_length);

	fill_magic_start(&(*bin));
	fill_name_comment(&(*bin));

	ft_strdel(&((*bin).f_contents)); //*********************** magic ept
	(*bin).f_contents = ft_strdup(file_contents); //*********************** magic ept
	printf("===>%s<===\n", (*bin).f_contents); 
	



	parse_commands(&(*bin)); //collecting commands labels and staff <==================== Molly

	// 



	if ((*bin).flag_a == 1)
	{
	 	ft_print_flag_a(&(*bin));
	 	return (0);
	}
	create_cor_file(&(*bin)); //creates the file iteslf and fills out the contents
	close((*bin).fd);
	return (1);

}

int 		main(int argc, char **argv)
{
	int 		i;
	t_binfile	bin;


	i = 0;
	if (argc == 1)
	{
		ft_print_usage();
		return (0);
	}
	init_bin(&bin);
	while(argv[i + 1])
	{
		if (!(ft_strcmp(argv[i], "-a")))
		{
			bin.flag_a = 1;
			//ft_printf("Oh God wee need to print a stripped version\n");
		}
		i++;
	}
	if (ft_strcmp(&argv[i][ft_strlen(argv[i]) - 2], ".s") != 0)
	{
		ft_print_inv_f(bin);
		return (0);
	}
	bin.arg_name = ft_strdup(argv[i]);
	bin.fd = open(argv[i],  O_RDONLY);

	if (bin.fd < 0)
	{
		ft_print_inv_f(bin);
		return (0);
	}
	bin.arg_length = (unsigned int)lseek(bin.fd, 0, SEEK_END);
	lseek(bin.fd, 0, SEEK_SET);
	ft_opening_file(&bin);

//printf("1111 =>>>> %s\n", bin.f_contents);
	

 	//what is that???????
 	
	//print_struct(&bin);

	ft_strdel(&(bin.arg_name));
	ft_printf("all good so far\n");


	return 0;
}

