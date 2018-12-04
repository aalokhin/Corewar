/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors_usage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:20:53 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/04 16:20:55 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				error_message_label(t_binfile *f, t_t *tk, char *l, char *arg)
{
	int			colomn;

	colomn = define_line_colomn(f->copy, arg, tk->line_num);
	if (ft_strstr(arg, "%:"))
	{
		ft_printf("No such label %s while attempting to dereference token ", l);
		ft_printf("[TOKEN][%0.3d:%0.3d] %s \"%s\"\n", tk->line_num + 1,\
		colomn + 1, "DIRECT_LABEL", arg);
	}
	else if (ft_strstr(arg, ":"))
	{
		ft_printf("No such label %s while attempting to dereference token ", l);
		ft_printf("[TOKEN][%0.3d:%0.3d] %s \"%s\"\n", tk->line_num + 1,\
		colomn + 1, "INDIRECT_LABEL", arg);
	}
	return (0);
}

int				error_command(t_binfile *file, char *str, int line_num)
{
	int			colomn;

	colomn = define_line_colomn(file->copy, str, line_num);
	ft_printf("Invalid instruction at token [TOKEN]");
	ft_printf("[%0.3d:%0.3d] INSTRUCTION \"%s\"\n", line_num + 1, colomn, str);
	return (0);
}

int				error_message(t_binfile *file, char *arg, int line_num)
{
	char		*e;
	int			colomn;

	colomn = define_line_colomn(file->copy, arg, line_num);
	if (ft_strchr(arg, 'r') && !(ft_strchr(arg, DIRECT_CHAR)) && !(ft_strchr(arg, LABEL_CHAR)))
		e = ft_strdup("REGISTER");
	else if (ft_strstr(arg, "%:"))
		e = ft_strdup("DIRECT_LABEL");
	else if (ft_strstr(arg, ":"))
		e = ft_strdup("INDIRECT_LABEL");
	else if (ft_strchr(arg, '%'))
		e = ft_strdup("DIRECT");
	else if (ft_atoi(arg) != 0)
		e = ft_strdup("INDIRECT");
	else if (ft_strchr(arg, SEPARATOR_CHAR))
		e = ft_strdup("SEPARATOR");
	else if (ft_strchr(arg, ':'))
		e = ft_strdup("LABEL");
	else
		e = ft_strdup("INSTRUCTION");
	ft_printf("Syntax error at token [TOKEN][%0.3d:%0.3d] %s \"%s\"\n",\
	line_num + 1, colomn, e, arg);
	ft_strdel(&e);
	return (0);
}

int				error_invalid_arg_type(t_t *command, int arg, int size)
{
	char		*type;

	if (size == 1)
		type = ft_strdup("register");
	else if (size == 2)
		type = ft_strdup("direct");
	else if (size == 3)
	{
		ft_printf("Invalid parameter count for instruction");
		ft_printf("%s\n", command->name_c);
		return (0);
	}
	else
		type = ft_strdup("indirect");
	ft_printf("Invalid parameter %d type %s for instruction %s\n",\
	arg, type, command->name_c);
	ft_strdel(&type);
	return (0);
}
