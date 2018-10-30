#include "asm.h"


void		init_bin(t_binfile	*bin)
{
	(*bin).fd = 0;
	(*bin).flag_a = 0;
	(*bin).arg_name = NULL;
	(*bin).arg_length = 0;
	(*bin).exec_code = NULL;
	(*bin).champ_size_nbr = 0;
	(*bin).comment = NULL;
	(*bin).name = NULL;
	(*bin).fd_file_out = 0;




	// printf(" ================>[%s]\n", bin->magic_start);

}

void 	print_struct(t_binfile	*bin)
{

// 	start_color();
// init_pair(1 , COLOR_GREEN, COLOR_BLACK);
// attron(COLOR_PAIR(11));
	printf("\nbin.arg_name ====>%s\n", bin->arg_name);
	printf("bin.fd ====>%d\n", bin->fd);
	printf("arg length ====>%u\n\n", bin->arg_length);
	//attroff( COLOR_PAIR(11));
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~MAGIC\n");
	
	printf("%x\n", 	(*bin).magic_start[3]);
	printf("%x\n", (*bin).magic_start[2]);
	printf("%x\n", (*bin).magic_start[1]);
	printf("%x\n", (*bin).magic_start[0]);

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
			ft_printf("Oh God wee need to print a stripped version\n");
		}
		i++;
	}
	if (ft_strcmp(&argv[i][ft_strlen(argv[i]) - 2], ".s") != 0)
	{
		ft_print_inv_f(bin);
		return (0);
	}

	bin.arg_name = ft_memalloc(sizeof(ft_strlen(argv[i]) + 1));
	ft_strcpy(bin.arg_name, argv[i]);


	bin.fd = open(argv[i],  O_RDONLY);




	if (bin.fd < 0)
	{
		ft_print_inv_f(bin);
		return (0);
	}
	bin.arg_length = (unsigned int)lseek(bin.fd, 0, SEEK_END);
	//lseek(bin.fd, 0, SEEK_SET); //what is that???????
	fill_magic_start(&bin);


	create_cor_file(&bin); //O_CREAT|O_WRONLY|O_TRUNC


	if (bin.flag_a == 1)
		ft_print_flag_a(&bin);

	ft_printf("all good so far\n");
	print_struct(&bin);
	
	return 0;
}





// void	ft_dir_n(char *arg, int lb, char **res, int *j)
// {
// 	unsigned int	num;

// 	num = (unsigned int)ft_atoi(&arg[1]);
// 	if (lb == 2)
// 		num = (unsigned short)num;
// 	if (lb == 4)
// 		(*res)[(*j)++] = (char)((num >> 24) & 255);
// 	if (lb == 4)
// 		(*res)[(*j)++] = (char)((num >> 16) & 255);
// 	(*res)[(*j)++] = (char)((num >> 8) & 255);
// 	(*res)[(*j)++] = (char)(num & 255);
// }