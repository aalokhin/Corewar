/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdynia <mdynia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:35 by mdynia            #+#    #+#             */
/*   Updated: 2018/12/05 18:28:36 by mdynia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*string_definer(char *str, int i)
{
	int		k;
	int		l;
	char	*string;

	k = i;
	l = 0;
	while (str[i] && str[i] != '\n')
		i++;
	string = (char *)ft_memalloc(sizeof(char) * (i - k + 1));
	while (str[k] && str[k] != '\n')
	{
		string[l] = str[k];
		l++;
		k++;
	}
	string[l] = '\0';
	return (string);
}

int		initial_validation_helper(t_binfile *file, char *str, int line, int i)
{
	int		start;
	char	cpy[2];
	char	*string;

	start = 0;
	while (str[i])
	{
		start = str[i] == '\n' ? i : start;
		if (!(WHITESPACE(str[i])) && str[i] != '-' && !ft_isdigit(str[i])
			&& str[i] != '_' && (str[i] < 97 || str[i] > 123)
			&& str[i] != LABEL_CHAR && str[i] != DIRECT_CHAR
			&& str[i] != SEPARATOR_CHAR)
		{
			cpy[0] = str[i];
			cpy[1] = '\0';
			string = string_definer(str, start + 1);
			line = define_line_num(file->copy, string, 0, 0);
			ft_printf("Lexical error at [%d:", line + 1);
			ft_printf("%d]\n", define_line_colomn(file->copy, cpy, line));
			ft_strdel(&string);
			return (0);
		}
		i++;
	}
	return (i);
}

int		initial_validation(t_binfile *file)
{
	char	*str;
	int		i;

	i = 0;
	str = file->f_contents;
	if (!file->f_contents[i])
	{
		ft_printf("Syntax error at token [TOKEN] END \"(null)\"\n");
	}
	i = initial_validation_helper(file, str, 0, 0);
	if (i == 0)
		return (0);
	if (str[i - 1] && str[i - 1] != '\n')
	{
		ft_printf("Syntax error - unexpected end of input ");
		ft_printf("(Perhaps you forgot to end with a newline ?)\n");
		return (0);
	}
	return (1);
}
