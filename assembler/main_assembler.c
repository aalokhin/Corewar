#include "asm.h"

void				init_bin(t_binfile	*bin)
{
	(*bin).fd = 0;
	(*bin).flag_a = 0;
	(*bin).arg_length = 0;
	(*bin).champ_size_nbr = 0;
	(*bin).fd_file_out = 0;
	(*bin).arg_name = NULL;
	(*bin).f_contents = NULL;
	(*bin).labels_list = NULL;
}

int 			init_check(t_binfile *bin)
{

	if (!(initial_validation(&(*bin))))
		return (0);
	if (!(parse_commands(&(*bin), 0, NULL, NULL)))
		return (0);
	if (!(label_distance(&(*bin))))
		return (0);
	if ((*bin).flag_a == 1)
	{
	 	ft_print_flag_a(&(*bin));
	 	flag_a_output(&(*bin));
	 	return (0);
	}
	return(1);
}

int				file_processing(t_binfile *bin)
{
	char file_contents[(*bin).arg_length + 1];	
	read((*bin).fd, file_contents, (*bin).arg_length);
	file_contents[(*bin).arg_length] = '\0';
	(*bin).f_contents = ft_strdup(file_contents);
	(*bin).copy = ft_strdup(file_contents);
	parse_file(&(*bin), &file_contents);
	fill_magic_start(&(*bin));
	if (!(fill_name_comment(&(*bin))))
	{
		ft_clean_all(bin);
		return (0);
	}
	// system("leaks asm");
	ft_strdel(&((*bin).f_contents)); //*********************** magic ept
	(*bin).f_contents = ft_strdup(file_contents); //*********************** magic ept
	if (init_check(bin) == 0)
	{
		ft_clean_all(bin);
		return (0);
	}
	create_cor_file(&(*bin)); //creates the file iteslf and fills out the contents
	close((*bin).fd);
	// system("leaks asm");
	ft_clean_all(bin);
	return (1);
}

int				ft_opening_file(char *s_file, int flag_a)
{
	t_binfile	bin;

	init_bin(&bin);
	if (flag_a == 1)
		bin.flag_a = 1;
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
		ft_clean_all(&bin);
		return (0);
	}
	bin.arg_length = (unsigned int)lseek(bin.fd, 0, SEEK_END);
	lseek(bin.fd, 0, SEEK_SET);
	return (file_processing(&bin));
}

char				*join_name_path(char *curdir, char *file)
{
	int 			len;
	char 			*path;
	char 			*new;

	len = ft_strlen(curdir);
	path = NULL;
	new = NULL;
	if (curdir[len - 1] == '/')
		path = ft_strjoin(curdir, file);
	else
	{
		new = ft_strnew(len + 1);
		new = ft_strncpy(new, curdir, len);
		new[len] = '/';
		path = ft_strjoin(new, file); 
		ft_strdel(&new);
	}
	return (path);
}

int 				ft_opening_directory(char *input, int flag_d, int flag_a)
{
	DIR				*dfd;
	struct dirent	*dp;
	char			*filename;

	filename = NULL;
	if ((dfd = opendir(input)) == NULL)
		return (0);
	while ((dp = readdir(dfd)) != NULL)
	{
		filename = join_name_path(input, dp->d_name);
		if (!CUR_DIR(dp->d_name[0]))
		{
			ft_opening_file(filename, flag_a);
			if (flag_d == 2)
				ft_opening_directory(filename, flag_d, flag_a);
		}
	}
	closedir(dfd);
	return (1);
}

int					main(int argc, char **argv)
{
	int				i;
	int				flag_a;
	int				flag_d;

	flag_a = 0;
	i = 0;
	if (argc == 1)
	{
		ft_print_usage();
		return (0);
	}
	if (!(ft_strcmp(argv[1], "-d")))
		flag_d = 1;
	else if (!(ft_strcmp(argv[1], "-D")))
		flag_d = 2;
	while (argv[i + 1])
	{
		if (!(ft_strcmp(argv[i], "-a")))
			flag_a = 1;		
		i++;
	}
	i = (flag_d || flag_a) ?  2 : 1;
	while (i < argc)
	{
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
	//system("leaks asm");

	return 0;
}

