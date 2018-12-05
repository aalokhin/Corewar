/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_assembler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:49:25 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/04 16:49:27 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				init_bin(t_binfile *bin)
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

int					init_check(t_binfile *bin)
{
	if (!(initial_validation(&(*bin))))
	{
		return (0);
	}
	if (!(parse_commands(&(*bin), 0, NULL, NULL)))
	{
		return (0);
	}
	if (!(label_distance(&(*bin))))
		return (0);
	if ((*bin).flag_a == 1)
	{
		ft_print_flag_a(&(*bin));
		flag_a_output(&(*bin));
		return (0);
	}
	return (1);
}

int					file_processing(t_binfile *bin)
{
	char file_contents[(*bin).arg_length + 1];

	read((*bin).fd, file_contents, (*bin).arg_length);
	file_contents[(*bin).arg_length] = '\0';
	(*bin).f_contents = ft_strdup(file_contents);
	(*bin).copy = ft_strdup(file_contents);
	parse_file(&(*bin), &file_contents);
	fill_magic_start(&(*bin));
	if (!(fill_name_comment(&(*bin), 0, 0)))
	{
		ft_clean_all(bin);
		return (0);
	}
	// system("leaks asm");
	ft_strdel(&((*bin).f_contents));
	(*bin).f_contents = ft_strdup(file_contents);
	if (init_check(bin) == 0)
	{
		ft_clean_all(bin);
		//system("leaks asm");
		return (0);
	}
	create_cor_file(&(*bin));
	close((*bin).fd);
	// system("leaks asm");
	ft_clean_all(bin);
	return (1);
}

int					parse_stdargs(int flag_a, int flag_d, char **argv, int argc)
{
	int				i;

	i = (flag_d || flag_a) ? 2 : 1;
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
	return (0);
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
	return (parse_stdargs(flag_a, flag_d, argv, argc));
}
