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

int		check_flag_n(char **argv, int argc, t_flags *params)
{
	int res;

	res = 0;
	if (ft_strcmp(argv[(*params).i], "-n") == 0 && (*params).j
		< MAX_PLAYERS && (*params).i + 1 < argc)
	{
		res = ft_atoi(argv[(*params).i + 1]);
		if (res > 0 && !check_if_norepeat_id(params, res, 1)
			&& res <= 65535)
		{
			(*params).pl_nbr[(*params).j][0] = 1;
			(*params).pl_nbr[(*params).j][1] = res;
			(*params).i += 2;
			return (1);
		}
		else
		{
			ft_printf("%s\n",
			"Error: Process number must be from 1 to 65535 and unique");
			exit(0);
		}
	}
	return (0);
}

int		check_flag_v(char **argv, int argc, t_flags *params)
{
	if (ft_strcmp(argv[(*params).i], "-v") == 0 &&
		(*params).i + 1 < argc)
	{
		if (ft_atoi(argv[(*params).i + 1]) >= 0 &&
			ft_atoi(argv[(*params).i + 1]) <= 65535)
		{
			(*params).v_verbosity = ft_atoi(argv[(*params).i + 1]);
			(*params).i += 2;
		}
		else
		{
			print_usage();
			exit(0);
		}
		return (1);
	}
	return (0);
}

int		check_flags_with_nbr(char **argv, int argc, t_flags *params)
{
	if (ft_strcmp(argv[(*params).i], "-dump") == 0 && (*params).i + 1 < argc)
	{
		if (ft_atoi(argv[(*params).i + 1]) > 0 &&
			ft_atoi(argv[(*params).i + 1]) <= 65535)
		{
			(*params).d_dumps_memory = ft_atoi(argv[(*params).i + 1]);
			(*params).i += 2;
			return (1);
		}
		else
		{
			ft_printf("%s\n",
			"Error: Dump number must be from 1 to 65535");
			exit(0);
		}
	}
	else if (check_flag_v(argv, argc, params))
		return (1);
	else if (check_flag_n(argv, argc, params))
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
		{
			ft_printf("%s\n", "Error: Too many champions");
			return (0);
		}
		(*params).j++;
		(*params).players[(*params).bots_quantity++] = argv[(*params).i];
		return (1);
	}
	else
	{
		ft_printf("%s %s\n", "Error: Can't read source file",
			argv[(*params).i]);
		print_usage();
		return (-1);
	}
}

int		check_flags_core(int argc, char **argv, t_flags *params)
{
	int res;

	while ((*params).i < argc)
	{
		if (ft_strcmp(argv[(*params).i], "-a") == 0)
			(*params).a_aff = 1;
		else if ((ft_strcmp(argv[(*params).i], "-dump") == 0 ||
		ft_strcmp(argv[(*params).i], "-v") == 0
		|| ft_strcmp(argv[(*params).i], "-n") == 0) && (*params).i + 1 >= argc)
		{
			print_usage();
			return (-2);
		}
		else if (check_flags_with_nbr(argv, argc, params))
			continue ;
		else if ((res = check_flags_nc_and_bots(argv, params)) <= 0)
			return (res);
		(*params).i++;
	}
	if ((*params).j == 0)
	{
		print_usage();
		return (-2);
	}
	return (1);
}
