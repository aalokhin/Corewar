/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalokhin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:07:52 by aalokhin          #+#    #+#             */
/*   Updated: 2018/12/05 17:07:54 by aalokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H
# define __ASM_H
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../op.h"
# include <dirent.h>
# define WHITESPACE(c)		(c == ' ' || c == '\t' || c =='\n')
# define NEW_LINE(c)		(c == '\n')
# define CUR_DIR(c)			(c == '.')
# define MAGIC_SIZE			4

typedef struct				s_op
{
	char					*name;
	int						nb_params;
	int						param_types[4];
	int						opcode;
	int						nb_cycles;
	char					*description;
	int						has_pcode;
	int						has_idx;
}							t_op;

typedef struct				s_t
{
	int						c_name;
	int						opcode;
	char					*name_c;
	char					*a[4];
	int						arguments;
	int						lbl_size;
	int						codage;
	int						args[3][2];
	int						bytes_above_i;
	int						has_codage;
	int						c_len;
	int						line_num;
	struct s_t				*next;

}							t_t;

typedef struct				s_lable
{
	t_t						*instruct;
	char					*label_name;
	struct s_lable			*next;
	struct s_lable			*prev;
	int						lbl_len;
	int						bytes_above;
	int						line_num;
}							t_lable;

typedef struct				s_binfile
{
	char					z[3];
	char					w[2];
	int						fd;
	int						fd_file_out;
	unsigned char			a[4];
	char					*f_contents;
	char					*copy;
	int						flag_a;
	char					*arg_name;
	char					*res_arg_name;
	unsigned int			arg_length;
	unsigned int			file_length;
	char					*name;
	char					*comment;
	unsigned int			champ_size_nbr;
	char					magic_start[4];
	char					champ_name[PROG_NAME_L + 1];
	char					champ_comment[COMMENT_L + 1];
	char					champ_size[4];
	char					*comma;
	char					*exec_code;
	char					*str_n;
	t_lable					*labels_list;
}							t_binfile;

int							label_distance(t_binfile *bin);
void						ft_print_usage();
void						ft_print_inv_f(char *s_file);
void						ft_print_flag_a(t_binfile *bin);
void						ft_print_inv_input();
void						ft_print_success(t_binfile *bin);
void						fill_magic_start(t_binfile *bin);
int							fill_name_comment(t_binfile *bin, size_t i,\
							size_t tmp);
int							ft_opening_file(char *s_file, int flag_a);
void						init_bin(t_binfile	*bin);
int							file_processing(t_binfile *bin);
void						create_cor_file(t_binfile *bin);
void						fill_corfile_contents(t_binfile *bin);
void						print_four_bytes(unsigned int src, int fd_out);
void						print_reg_to_file(int i, t_t *tmp, int fd_out);
void						print_ind_to_file(int i, t_t *tmp, int fd_out);
void						print_dir_to_file(int i, t_t *tmp, int fd_out);
void						print_inst_file(t_t *tmp, size_t i, t_binfile *bin);
void						ft_zero_what_left(t_binfile *bin,\
							size_t *c, char (*file)[]);
void						clean_name_comment(t_binfile *bin,\
							char (*contents)[]);
void						clean_spaces(t_binfile *bin, char (*contents)[]);
void						move_name_comment(char (*contents)[], size_t *i);
void						clean_new_lines(t_binfile *bin, char (*contents)[]);
void						fill_corfile_contents(t_binfile *bin);
void						parse_file(t_binfile *bin, char (*contents)[]);
int							ft_clean_parse(char **parse);
int							parse_commands(t_binfile *file, int i,\
							char **str_n, char **str);
int							ft_cmd_lbls(char	*c_name);
int							label_name_is_valid(t_binfile *file,\
							t_lable *label, char *str);
int							arguments_validator(t_binfile *file,\
							t_t *token, char *arg, int i);
int							error_message(t_binfile *file,\
							char *arg, int line_num);
int							error_invalid_arg_type(t_t *command,\
							int arg, int type);
int							error_message_label(t_binfile *file,\
							t_t *token, char *label, char *arg);
int							error_command(t_binfile *file,\
							char *str, int line_num);
int							define_line_num(char *copy, \
							char *str_n, int f, int l);
int							define_line_colomn(char *copy,\
							char *arg, int line_num);
int							initial_validation(t_binfile *file);
void						token_length(t_t *token, int i, t_lable *label);
void						label_length(t_binfile *file, t_lable	*label);
void						file_length(t_binfile *file);
int							bytes_above_i(t_lable *label);
void						bytes_above_filler(t_binfile *file, t_lable *label);
void						flag_a_output(t_binfile *bin);
void						print_arg_chars(t_t	*instruct);
void						ind_dir_print(int arg0, int arg, int lbl_size);
void						print_instr_args(t_t *instruct);
void						print_instr_args2(t_t *instruct);
char						*join_name_path(char *curdir, char *file);
int							ft_opening_directory(char *input,\
							int flag_d, int flag_a);
void						ft_clean_all(t_binfile	*bin);
int							token_codage(t_t *token, int i);
int							command_name(char *name, t_t *token);
t_lable						*labels_linker(t_binfile *file, t_lable *label);
void						command_linker(t_lable *label, t_t *token);
char						*string_definer(char *str, int i);
int							initial_validation(t_binfile *file);
int							cmd_linker_add(t_binfile *file, t_lable *label,\
							t_t *token);
int							my_end(t_binfile *file, t_lable *label,\
							char **str_n, char **comma);
int							label_filler(t_binfile *file, t_lable **label,\
							char **str, int *i);
int							no_name_comment(t_binfile *file, char **str_n,\
							char **comma);
int							clean(char **str, char **str_n, char **comma);
char						*space_adder(char **str);
int							fill_command_name(t_binfile *file, t_t *token,\
							char **str, int *i);
int							val_n_c(char *file, int i, int j);
int							comma_checker(t_t *token, char *str, int l, int k);
int							argument_adder2(char *str);
int							all_digits(char *str);

#endif
