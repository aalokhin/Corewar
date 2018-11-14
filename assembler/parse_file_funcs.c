#include "asm.h"

void				skip_name_comment(size_t *count, char (*contents)[])
{
	size_t			k;

	k = 0;
	while (k != 4)
	{
		if ((*contents)[(*count)] == '"')
			k++;
		(*count)++;
	}
	while ((*contents)[(*count)] && (*contents)[(*count)] != '\n')
		(*count)++;
}

void				ft_zero_what_left(t_binfile *bin, size_t *c, char (*file)[])
{
	while ((*c) < bin->arg_length)
	{
		(*file)[(*c)] = '\0';
		(*c)++;
	}
}

void				clean_name_comment(t_binfile *bin, char (*contents)[])
{
	size_t			i;
	size_t			len;
	size_t			k;

	i = 0;
	k = 0;
	len = 0;
	while (i < bin->arg_length)
	{
		if (ft_strncmp(&(*contents)[i], ".name", 5) == 0 ||\
			ft_strncmp(&(*contents)[i], ".comment", 8) == 0)
		{
			len = 0;
			while ((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);
}

void				ft_clean_commas(char (*contents)[])
{
	size_t			i;

	i = 0;
	while ((*contents)[i])
	{
		if ((*contents)[i] == ',')
			(*contents)[i] = ' ';
		i++;
	}
}

void				clean_spaces(t_binfile *bin, char (*contents)[])
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while ((*contents)[i])
	{
		while ((*contents)[i] != '\n' && WHITESPACE((*contents)[i]))
			++i;
		if (j > 0 && (*contents)[j - 1] != '\n' && i > 0\
		&& WHITESPACE((*contents)[i - 1]))
		{
			(*contents)[j] = ' ';
			j++;
		}
		if ((*contents)[i] && ((*contents)[i] == '\n' ||\
		!WHITESPACE((*contents)[i])))
		{
			ft_memmove(&(*contents)[j], &(*contents)[i], 1);
			j++;
		}
		i++;
	}
	ft_zero_what_left(bin, &j, contents);
	ft_clean_commas(contents);
}

void				clean_new_lines(t_binfile *bin, char (*contents)[])
{
	size_t			j;
	size_t			i;
	size_t			len;

	j = 0;
	i = 0;
	len = 0;
	while ((*contents)[i])
	{
		if ((*contents)[i] == '\n')
		{
			while ((*contents)[i + 1] == '\n')
				++i;
			if ((*contents)[0] == '\n')
				i++;
		}
		ft_memmove(&(*contents)[j], &(*contents)[i], 1);
		j++;
		i++;
	}
	ft_zero_what_left(bin, &j, contents);
}

void				remove_comments(t_binfile *bin, char (*contents)[])
{
	size_t			i;
	size_t			len;
	size_t			k;

	len = 0;
	i = 0;
	k = 0;
	while (i < bin->arg_length)
	{
		if ((*contents)[i] == '#' || (*contents)[i] == ';')
		{
			len = 0;
			while ((*contents)[i] && (*contents)[i] != '\n')
			{
				len++;
				i++;
			}
		}
		ft_memmove(&(*contents)[k], &(*contents)[i], len);
		k++;
		i++;
	}
	ft_zero_what_left(bin, &k, contents);
}

void				parse_file(t_binfile *bin, char (*contents)[])
{
	remove_comments(bin, contents);
	clean_name_comment(bin, contents);
	clean_spaces(bin, contents);
	clean_new_lines(bin, contents);
}
