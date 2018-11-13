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
	(*bin).copy = ft_strdup(file_contents);
	parse_file(&(*bin), &file_contents);
	//ft_space(&file_contents, (int)bin->arg_length);

	fill_magic_start(&(*bin));
	//if (!
	fill_name_comment(&(*bin));
	// {
	// 	printf("%s\n",  "no name or comment");
	// 	return (0);
	// }

	ft_strdel(&((*bin).f_contents)); //*********************** magic ept
	(*bin).f_contents = ft_strdup(file_contents); //*********************** magic ept
	//printf("===>%s<===\n", (*bin).f_contents); 
	if (!(parse_commands(&(*bin))))//collecting commands labels and staff <==================== Molly
		return (0);

	label_distance(&(*bin));

	// 
	//main_printer(&(*bin)); // printing stuff <==================== Molly


	if ((*bin).flag_a == 1)
	{
	 	ft_print_flag_a(&(*bin));
	 	flag_a_output(&(*bin));
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
	//printf("============> %s\n", s_file);

	init_bin(&bin);
	if (flag_a == 1)
	{
		bin.flag_a = 1;
	}
	if (ft_strcmp(&s_file[ft_strlen(s_file) - 2], ".s") != 0)
	{
		ft_print_inv_f(s_file);
		return (0);
	}
	bin.arg_name = ft_strdup(s_file);
	bin.fd = open(s_file,  O_RDONLY);

	if (bin.fd < 0)
	{
		ft_print_inv_f(s_file);
		return (0);
	}
	bin.arg_length = (unsigned int)lseek(bin.fd, 0, SEEK_END);
	lseek(bin.fd, 0, SEEK_SET);



	return (file_processing(&bin));

}

char 				*join_name_path(char *curdir, char *file)
{
	int 			len;
	char 			*path;
	char 			*new;

	len = ft_strlen(curdir);
	path = NULL;
	new = NULL;
	
	if (curdir[len - 1] == '/')
	{
		path = ft_strjoin(curdir, file);
	}
	else
	{
		new = ft_strnew(len + 1);
		new = ft_strncpy(new, curdir, len);
		new[len] = '/';
		//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~%s\n", new);
		path = ft_strjoin(new, file); 
		ft_strdel(&new);
	}
	return(path);
}


int 				ft_opening_directory(char *input, int flag_d, int flag_a)
{
	DIR 			*dfd; //fd of dir
	struct dirent 	*dp; //pointer dir
	//char 			*s_file; //file name  .s
	char 			*filename;

	filename = NULL;

	
	//printf("input ==> %s\n", input);

	if ((dfd = opendir(input)) == NULL)
		return (0);
	//printf("hurra it's dir \n");
	while((dp = readdir(dfd)) != NULL)
	{
		//printf("~~~~~~~~~~~~~~~~~~~~>>>>> filename in dir: is  %s\n", dp->d_name);

		filename = join_name_path(input, dp->d_name);


		if (!CUR_DIR(dp->d_name[0]))
		{
			//printf("======================> resulting filename is  %s\n", filename);

			ft_opening_file(filename, flag_a);
			if(flag_d == 2)
				ft_opening_directory(filename, flag_d, flag_a);

		}
	}

	closedir(dfd);

	return (1);
}

int 		main(int argc, char **argv)
{
	int 		i;
	int 		flag_a;
	int 		flag_d;
	//int 		flags[3];



	flag_a = 0;
	i = 0;
	if (argc == 1)
	{
		ft_print_usage();
		return (0);
	}

	if (!(ft_strcmp(argv[1], "-d")))
	{
		flag_d = 1;		
		//ft_printf("Oh God wee need to print a stripped version\n");
	}
	else if (!(ft_strcmp(argv[1], "-D")))
	{
		flag_d = 2;
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
	i = (flag_d || flag_a) ?  2 : 1; 

	while (i < argc)
	{
		//printf("%s\n", argv[i]);
		if (flag_d != 1 && flag_d != 2)
		{
			if (!ft_opening_file(argv[i], flag_a))
				return (0);
		}
		else
		{
			if (!ft_opening_directory(argv[i], flag_d, flag_a))
				if (!ft_opening_file(argv[i], flag_a))
					return (0);
		}
		i++;
	}
	

//printf("1111 =>>>> %s\n", bin.f_contents);
	

 	//what is that???????
 	
	//print_struct(&bin);


	//ft_printf("all good so far\n");


	return 0;
}

