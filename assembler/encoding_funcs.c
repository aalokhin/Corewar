#include "asm.h"

void			fill_magic_start(t_binfile *bin)
{
	bin->magic_start[3] = (char)(COREWAR_EXEC_MAGIC & 255);
	bin->magic_start[2] = (char)((COREWAR_EXEC_MAGIC >> 8) & 255);
	bin->magic_start[1] = (char)((COREWAR_EXEC_MAGIC >> 16) & 255);
	bin->magic_start[0] = (char)((COREWAR_EXEC_MAGIC >> 24) & 255);
}

int			fill_str_help(char *str, size_t *i, size_t *tmp)
{
	while (str[(*i)] != '"')
		(*i)++;
	*tmp = ++(*i);
	while (str[(*i)] != '"')
	{
		(*i)++;
		// if (!(str[(*i)]))
		// 	return (0);
	}
	return (1);
}

int				fill_name_comment(t_binfile *bin)
{
	size_t		i;
	char		*str;
	size_t		tmp;

	i = 0;
	tmp = 0;
	if (ft_strstr(bin->f_contents, NAME_CMD_STRING) &&\
	ft_strstr(bin->f_contents, COMMENT_CMD_STRING))
	{
		str = ft_strstr(bin->f_contents, NAME_CMD_STRING);
		if (!(fill_str_help(str, &i, &tmp)))
			return (error_message(bin, NAME_CMD_STRING, define_line_num(bin->copy, NAME_CMD_STRING, 0, 0)));
		bin->name = ft_strnew(PROG_NAME_L);
		ft_strncpy(bin->name, &str[tmp], i - tmp);
		str = ft_strstr(bin->f_contents, COMMENT_CMD_STRING);
		i = 0;
		tmp = 0;
		if (!(fill_str_help(str, &i, &tmp)))
			return (error_message(bin, COMMENT_CMD_STRING, define_line_num(bin->copy, COMMENT_CMD_STRING, 0, 0)));
		bin->comment = ft_strnew(COMMENT_L);
		ft_strncpy(bin->comment, &str[tmp], i - tmp);
		return (1);
	}
	else
		return (2);
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
