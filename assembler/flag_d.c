/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:54:21 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/04 16:54:29 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_opening_file(char *s_file, int flag_a)
{
	t_binfile		bin;

	init_bin(&bin);
	if (flag_a == 1)
		bin.flag_a = 1;
	if (ft_strcmp(&s_file[ft_strlen(s_file) - 2], ".s") != 0)
	{
		ft_print_inv_f(s_file);
		return (0);
	}
	bin.arg_name = ft_strdup(s_file);
	bin.fd = open(s_file, O_RDONLY);
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
	int				len;
	char			*path;
	char			*new;

	len = ft_strlen(curdir);
	path = NULL;
	new = NULL;
	if (curdir[len - 1] == '/')
	{
		path = ft_strjoin(curdir, file);
		//ft_strdel(&curdir);
	}
	else
	{
		new = ft_strnew(len + 1);
		new = ft_strncpy(new, curdir, len);
		new[len] = '/';
		//ft_strdel(&curdir);
		path = ft_strjoin(new, file);
		ft_strdel(&new);
	}
	return (path);
}

int					ft_opening_directory(char *input, int flag_d, int flag_a)
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
		ft_strdel(&filename);
	}
	closedir(dfd);
	return (1);
}
