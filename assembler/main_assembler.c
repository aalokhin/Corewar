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

}

void 	print_struct(t_binfile	*bin)
{
	printf("bin.arg_name ====>%s\n", bin->arg_name);
	printf("bin.fd ====>%d\n", bin->fd);
	printf("arg length ====>%u\n", bin->arg_length);
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
	ft_strcpy(bin.arg_name, (argv[i]));
	bin.fd = open(bin.arg_name,  O_RDONLY);
	bin.arg_length = (unsigned int)lseek(bin.fd, 0, SEEK_END);
	//lseek(bin.fd, 0, SEEK_SET); //what is that???????

	print_struct(&bin);

	if (bin.flag_a == 1)
		ft_print_flag_a(&bin);

	ft_printf("all good so far\n");
	
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