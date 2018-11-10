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

int 	file_processing(t_binfile *bin)
{
	char file_contents[(*bin).arg_length + 1];
	
	read((*bin).fd, file_contents, (*bin).arg_length);
	file_contents[(*bin).arg_length] = '\0';
	(*bin).f_contents = ft_strdup(file_contents);
	parse_file(&(*bin), &file_contents);
	//ft_space(&file_contents, (int)bin->arg_length);

	fill_magic_start(&(*bin));
	if (!fill_name_comment(&(*bin)))
	{
		printf("%s\n",  "no name or comment");
		return (0);
	}

	ft_strdel(&((*bin).f_contents)); //*********************** magic ept
	(*bin).f_contents = ft_strdup(file_contents); //*********************** magic ept
	//printf("===>%s<===\n", (*bin).f_contents); 
	if (!(parse_commands(&(*bin))))//collecting commands labels and staff <==================== Molly
	{
		printf("return in parsing\n");
		return (0);
	}

	label_distance(&(*bin));

	// 
	//main_printer(&(*bin)); // printing stuff <==================== Molly


	if ((*bin).flag_a == 1)
	{
	 	ft_print_flag_a(&(*bin));
	 	return (0);
	}
	create_cor_file(&(*bin)); //creates the file iteslf and fills out the contents
	close((*bin).fd);
	ft_strdel(&((*bin).arg_name));
	//ft_printf("all good so far\n");
	return (1);
}



int	 	ft_opening_file(char *s_file, int flag_a)
{
	t_binfile	bin;
	printf("============> %s\n", s_file);

	init_bin(&bin);
	if (flag_a == 1)
	{
		bin.flag_a = 1;
	}
	if (ft_strcmp(&s_file[ft_strlen(s_file) - 2], ".s") != 0)
	{
		ft_print_inv_f();
		return (0);
	}
	bin.arg_name = ft_strdup(s_file);
	bin.fd = open(s_file,  O_RDONLY);

	if (bin.fd < 0)
	{
		ft_print_inv_f();
		return (0);
	}
	bin.arg_length = (unsigned int)lseek(bin.fd, 0, SEEK_END);
	lseek(bin.fd, 0, SEEK_SET);



	return (file_processing(&bin));

}

int 		ft_opening_directory(char *input, int flag_d, int flag_a)
{
	DIR 	*dir;

	flag_d = flag_a;

	dir = opendir(input);
	if (dir == NULL)
		return (0);
	else
	{
		printf("hurra it's dir \n");
		return (0);
	}
}

int 		main(int argc, char **argv)
{
	int 		i;
	int 		flag_a;
	int 		flag_d;

	flag_a = 0;
	i = 0;
	if (argc == 1)
	{
		ft_print_usage();
		return (0);
	}

	if (!(ft_strcmp(argv[1], "-D")))
	{
		flag_d = 1;		
		//ft_printf("Oh God wee need to print a stripped version\n");
	}
	
	while(argv[i + 1])
	{
		if (!(ft_strcmp(argv[i], "-a")))
		{
			flag_a = 1;		
			//ft_printf("Oh God wee need to print a stripped version\n");
		}
		i++;
	}
	i = 1;


	while (i < argc)
	{
		//printf("%s\n", argv[i]);
		if (!ft_opening_directory(argv[i], flag_d, flag_a))
			if (!ft_opening_file(argv[i], flag_a))
				return (0);
		i++;
	}
	

//printf("1111 =>>>> %s\n", bin.f_contents);
	

 	//what is that???????
 	
	//print_struct(&bin);


	//ft_printf("all good so far\n");


	return 0;
}

