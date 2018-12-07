/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdynia <mdynia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 22:24:03 by mdynia            #+#    #+#             */
/*   Updated: 2018/11/18 22:24:06 by mdynia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			define_line_num_h(char *copy, char *str_n, int *f, int l)
{
	while (copy[*f] && copy[*f] != '\n')
	{
		while ((WHITESPACE(copy[*f]) && (copy[*f] != '\n'))\
			|| copy[*f] == SEPARATOR_CHAR)
			(*f)++;
		while (WHITESPACE(str_n[l]))
			l++;
		if (copy[*f] != str_n[l])
			return (0);
		else if (copy[*f] == str_n[l])
		{
			(*f)++;
			l++;
			while (WHITESPACE(str_n[l]))
				l++;
			if (str_n[l] == '\0')
				return (1);
		}
	}
	return (0);
}

int			define_line_num(char *copy, char *str_n, int f, int k)
{
	while (copy[f])
	{
		if (copy[f] == '\n')
			k++;
		else
		{
			if (define_line_num_h(copy, str_n, &f, 0))
				return (k);
			if (copy[f] == '\n')
				k++;
		}
		f++;
	}
	return (0);
}

int			exact_colomn(char *copy, char *arg, int i, int a)
{
	int		l;

	l = i;
	while (copy[i] != '\n' && arg[a])
	{
		if (copy[i] == arg[a])
		{
			i++;
			a++;
			if (arg[a] == '\0')
			{
				if (ft_strchr(arg, 'r') || ft_strchr(arg, DIRECT_CHAR)\
	|| ((ft_strchr(arg, LABEL_CHAR)) && arg[ft_strlen(arg) - 1] != LABEL_CHAR))
					return (i - l - a);
				return (i - l - a + 1);
			}
		}
		if (copy[i] != arg[a])
		{
			i++;
			a = 0;
		}
	}
	return (0);
}

int			define_line_colomn(char *copy, char *arg, int line_num)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (copy[i])
	{
		if (copy[i] == '\n' && ++n)
		{
			i += copy[i + 1] != '\n' ? 1 : 0;
			if (n == line_num)
				return (exact_colomn(copy, arg, i, 0));
		}
		i++;
	}
	return (-1);
}
