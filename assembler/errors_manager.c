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

int		define_line_num(char *copy, char *str_n, int f, int l)
{
	int 	k = 0;

	while (copy[f])
	{
		if (copy[f] == '\n')
			k++;
		else
		{
			l = 0;
			while (copy[f] && copy[f] != '\n' && l != -1)
			{
				while ((WHITESPACE(copy[f]) && (copy[f] != '\n'))|| copy[f] == ',')
					f++;
				while (WHITESPACE(str_n[l]) || str_n[l] == ',')
					l++;
				if (copy[f] != str_n[l])
					l = -1;
				if (copy[f] == str_n[l])
				{
					f++;
					l++;
					while (WHITESPACE(str_n[l]))
						l++;
					if (str_n[l] == '\0')
						return (k);
				}
			}
			if (copy[f] == '\n')
				k++;
		}
		f++;
	}
	return (0);
}

int 		define_line_colomn(char *copy, char *arg, int line_num)
{
	int		i = 0;
	int 	a = 0;
	int 	l = 0;
	int		n = 0;

	while (copy[i])
	{
		if (copy[i] == '\n' && n++)
		{
			i += copy[i + 1] != '\n' ? 1 : 0;
			if (n == line_num)
			{
				l = i;
				while (copy[i] != '\n' && arg[a])
				{
					if (copy[i] == arg[a])
					{
						i++; 
						a++;
						if (arg[a] == '\0')
						{
							if (ft_strchr(arg, 'r') || ft_strchr(arg, '%'))
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
			}
		}
		i++;
	}
	return (-1);
}