/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:58:58 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/12/04 16:59:01 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

int		check_flag_v(char **argv, int argc, t_flags *params)
{
	if (ft_strcmp(argv[(*params).i], "-v") == 0 && (*params).i + 1 < argc)
	{
		if (ft_atoi(argv[(*params).i + 1]) > 0)
		{
			(*params).v_verbosity = ft_atoi(argv[(*params).i + 1]);
			(*params).i += 2;
		}
		else
			(*params).i++;
		return (1);
	}
	else if (ft_strcmp(argv[(*params).i], "-n") == 0 && (*params).j
		< MAX_PLAYERS && (*params).i + 1 < argc)
	{
		if (ft_atoi(argv[(*params).i + 1]) > 0)
		{
			(*params).pl_nbr[(*params).j][0] = 1;
			(*params).pl_nbr[(*params).j][1] = ft_atoi(argv[(*params).i + 1]);
			(*params).i += 2;
		}
		else
			(*params).i++;
		return (1);
	}
	return (0);
}

int		check_flags_with_nbr(char **argv, int argc, t_flags *params)
{
	if (ft_strcmp(argv[(*params).i], "-d") == 0 && (*params).i + 1 < argc)
	{
		if (ft_atoi(argv[(*params).i + 1]) > 0)
		{
			(*params).d_dumps_memory = ft_atoi(argv[(*params).i + 1]);
			(*params).i += 2;
		}
		else
			(*params).i++;
		return (1);
	}
	else if (check_flag_v(argv, argc, params))
		return (1);
	return (0);
}

int		check_flags_nc_and_bots(char **argv, t_flags *params)
{
	if (ft_strcmp(argv[(*params).i], "-nc") == 0)
	{
		(*params).ncurses = 1;
		return (1);
	}
	else if (ft_strchr(argv[(*params).i], '.') && ft_strcmp(&
	(argv[(*params).i][ft_strlen(argv[(*params).i]) - 4]), ".cor") == 0)
	{
		if ((*params).bots_quantity == MAX_PLAYERS)
			return (0);
		(*params).j++;
		(*params).players[(*params).bots_quantity++] = argv[(*params).i];
		return (1);
	}
	else
		return (-1);
}

int		check_flags_core(int argc, char **argv, t_flags *params)
{
	while ((*params).i < argc)
	{
		if (ft_strcmp(argv[(*params).i], "-a") == 0)
			(*params).a_aff = 1;
		else if ((ft_strcmp(argv[(*params).i], "-d") == 0 ||
		ft_strcmp(argv[(*params).i], "-v") == 0
		|| ft_strcmp(argv[(*params).i], "-n") == 0) && (*params).i + 1 >= argc)
		{
			print_usage();
			return (-2);
		}
		else if (check_flags_with_nbr(argv, argc, params))
			continue ;
		else if (check_flags_nc_and_bots(argv, params) <= 0)
			return (check_flags_nc_and_bots(argv, params));
		(*params).i++;
	}
	if ((*params).j == 0)
	{
		print_usage();
		return (-2);
	}
	(*params).j = 0;
	return (1);
}
