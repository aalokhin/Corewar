/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dim_arr_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 16:23:14 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/12/12 16:23:41 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	**two_dim_arr_mem(char **field, int x, int y, char c)
{
	int i;
	int j;

	i = 0;
	field = (char **)malloc(sizeof(char *) * x);
	while (i < x)
	{
		field[i] = (char *)malloc(y);
		i++;
	}
	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			field[i][j] = c;
			j++;
		}
		i++;
	}
	return (field);
}
