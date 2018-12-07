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

static t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

char		*space_adder(char **str)
{
	char	*cmd;
	char	*cpy;
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

int			clean(char **str, char **str_n, char **comma)
{
	ft_clean_parse(str);
	ft_clean_parse(str_n);
	ft_clean_parse(comma);
	return (0);
}

int			comma_checker(t_t *token, char *str)
{
	int		l = -1;
	int 	k = -1;
	int 	comma = 0;
	char 	*string;

	while (str[++l])
		comma += str[l] == SEPARATOR_CHAR ? 1 : 0;
	if (g_op_tab[token->c_name].nb_params == comma + 1)
	{
		string = ft_strstr(str, token->a[0]);
		while (string[++k] && comma != 0)
			comma -= string[k] == SEPARATOR_CHAR ? 1 : 0;
		while (string[k])
		{
			if (!(WHITESPACE(string[k])))
				return (1);
			k++;
		}
	}
	ft_printf("No/Extra SEPARATOR_CHAR - line [%0.3d]\n", token->line_num + 1);
	return (0);
}

int			fill_command_name(t_binfile *file, t_t *token, char **str, int *i)
{
	char	*copy;

	copy = NULL;
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
