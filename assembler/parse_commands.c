/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdynia <mdynia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:26:45 by mdynia            #+#    #+#             */
/*   Updated: 2018/12/06 16:26:51 by mdynia           ###   ########.fr       */
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

int			argument_adder(char *str)
{
	if ((ft_strchr(str, 'r') && !(ft_strchr(str, DIRECT_CHAR))) &&
		!(ft_strchr(str, LABEL_CHAR)))
		return (1);
	else if (ft_strchr(str, DIRECT_CHAR))
		return (10);
	else
		return (11);
}

int			argument_adder2(char *str)
{
	if ((ft_strchr(str, 'r') && !(ft_strchr(str, DIRECT_CHAR))) &&
		!(ft_strchr(str, LABEL_CHAR)))
		return (1);
	else if (ft_strchr(str, DIRECT_CHAR))
		return (2);
	else
		return (3);
}

int			arguments_filler(t_binfile *file, t_t *t, char **s, int *i)
{
	int		a;

	a = 0;
	while (a < g_op_tab[t->c_name].nb_params && s[*i])
	{
		if (!(arguments_validator(file, t, s[*i], a)))
			return (0);
		t->args[a][0] = argument_adder(s[*i]);
		t->a[a++] = ft_strdup(s[*i]);
		if (a == g_op_tab[t->c_name].nb_params)
		{
			if (s[*i + 1])
				return (error_invalid_arg_type(t, *i,
				argument_adder2(s[*i + 1])));
			break ;
		}
		(*i)++;
	}
	if (a != g_op_tab[t->c_name].nb_params)
		return (error_invalid_arg_type(t, *i, 3));
	return (1);
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
	return (0);
}


int			parse_commands(t_binfile *file, int k, char **str_n, char **str)
{
	t_t		*token;
	t_lable	*label;
	char **comma;
	int		i;

	i = 0;
	token = NULL;
	label = NULL;
	str_n = (ft_strsplit(file->f_contents, '\n'));
	comma = (ft_strsplit(file->comma, '\n'));
	if (!no_name_comment(file, str_n))
		return (0);
	while (str_n[++k])
	{
		str = ft_strsplit(str_n[k], ' ');
		if (i == 0 && !(ft_strchr(str[i], DIRECT_CHAR)) &&\
	(ft_strchr(str[i], LABEL_CHAR)) && !(label_filler(file, &label, str, &i)))
			return (clean(str, str_n));
		if (str[i])
		{
			if (!label)
				label = (t_lable *)ft_memalloc(sizeof(t_lable));
			token = (t_t *)ft_memalloc(sizeof(t_t));
			token->line_num = define_line_num(file->copy, str_n[k], 0, 0);
			if ((!fill_command_name(file, token, &(str[i]), &i))\
				|| (++i >= 0 && (!arguments_filler(file, token, str, &i))))
				return (cmd_linker_add(file, label, token) ? clean(str, str_n) : 0);
			token_to_add(label, token);
			if (!comma_checker(token, comma[k]))
			{
				ft_printf("No/Extra SEPARATOR_CHAR - line [%0.3d]\n", token->line_num + 1);
				return (0);
			}
		}
		i = ft_clean_parse(str);
	}
	return (my_end(file, label, str_n));
}
