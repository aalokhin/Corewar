#include "asm.h"

void			fill_magic_start(t_binfile *bin)
{
	bin->magic_start[3] = (char)(COREWAR_EXEC_MAGIC & 255);
	bin->magic_start[2] = (char)((COREWAR_EXEC_MAGIC >> 8) & 255);
	bin->magic_start[1] = (char)((COREWAR_EXEC_MAGIC >> 16) & 255);
	bin->magic_start[0] = (char)((COREWAR_EXEC_MAGIC >> 24) & 255);
}

void			fill_str_help(char *str, size_t *i, size_t *tmp)
{
	while (str[(*i)] != '"')
		(*i)++;
	*tmp = ++(*i);
	while (str[(*i)] != '"')
		(*i)++;
}

int				fill_name_comment(t_binfile *bin)
{
	size_t		i;
	char		*str;
	size_t		tmp;
	char 		a;

	a = 22;
	i = 0;
	tmp = 0;
	if (ft_strstr(bin->f_contents, ".name") &&\
	ft_strstr(bin->f_contents, ".comment"))
	{
		str = ft_strstr(bin->f_contents, ".name");
		// if (ft_strchr(str, a) && ft_strchr(ft_strchr(str, a), a))
			fill_str_help(str, &i, &tmp);
		// else
		// 	return (error_message(bin, NULL, 1));
		bin->name = ft_strnew(PROG_NAME_LENGTH);
		ft_strncpy(bin->name, &str[tmp], i - tmp);
		str = ft_strstr(bin->f_contents, ".comment");
		i = 0;
		tmp = 0;
		// if (ft_strchr(str, a) && ft_strchr(ft_strchr(str, a), a))
			fill_str_help(str, &i, &tmp);
		// else
		// 	return (error_message(bin, NULL, 2));
		bin->comment = ft_strnew(COMMENT_LENGTH);
		ft_strncpy(bin->comment, &str[tmp], i - tmp);
		return (1);
	}
	else
		return (0);
}

void				create_cor_file(t_binfile *bin)
{
	char			*corfile;
	unsigned int	len;

	len = ft_strlen(bin->arg_name);
	corfile = ft_strnew(len + 3);
	if (!corfile)
		return ;
	ft_strncpy(corfile, bin->arg_name, len - 1);
	ft_strcpy(&corfile[len - 1], "cor");
	bin->res_arg_name = ft_strdup(corfile);
	bin->fd_file_out = open(corfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	ft_strdel(&corfile);
	fill_corfile_contents(bin);
}
