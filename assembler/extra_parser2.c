/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdynia <mdynia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:07:22 by mdynia            #+#    #+#             */
/*   Updated: 2018/12/06 16:07:24 by mdynia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*space_adder(char **str)
{
	char	*cmd;
	char 	*cpy;
	int		i;

	i = 0;
	cpy = *str;
	while (cpy[i])
	{
		if (cpy[i] == DIRECT_CHAR || cpy[i] == LABEL_CHAR)
			break ;
		i++;
	}
	cmd = ft_strsub(cpy, 0, i);
	*str = ft_strsub(cpy, i, ft_strlen(cpy));
	ft_strdel(&cpy);
	return (cmd);
}

int	clean(char **str, char **str_n)
{
	ft_clean_parse(str);
	ft_clean_parse(str_n);
	return (0);
}

int 	fill_command_name(t_binfile *file, t_t *token, char **str, int *i)
{
	char *copy =  NULL;

	if (ft_strchr(*str, DIRECT_CHAR) || ft_strchr(*str, LABEL_CHAR))
	{
		copy = space_adder(str);
		if (command_name(copy, token) == -1)
		{
			error_command(file, copy, token->line_num);
			ft_strdel(&copy);
			return (0);
		}
		ft_strdel(&copy);
		*i -= 1; 
	}
	else if (command_name(*str, token) == -1)
	{
		error_command(file, *str, token->line_num);
		return (0);
	}
	return (1);
}