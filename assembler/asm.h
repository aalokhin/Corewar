
#ifndef __ASM_H
# define __ASM_H

# include <fcntl.h>          
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../op.h"

#include <stdio.h>

// # define ARG1(c) (s = {"aff", "fork" "zjmp" || "live", "lfork"
// # define ARG2(c) (c == 'C' || c == 's' || c == 'S' || c == 'u')


// typedef struct 			s_arg
// {
// 	int 			bytes_len;
// 	char 			*line;
// 	unsigned char  	*arg;
	

// 	int 			is_dir;
// 	int 			distance;
// 	struct s_arg	*next;
// }						t_arg;

typedef struct			s_t  //minimum
{
	int					c_name; // order number of "live"
	int 				opcode;
	char 				*name_c; // 
	char 				*a[4]; // for codage T_REG r 01 T_DIR % 10 T_IND 11 
	



	int 				arguments; //  {T_DIR} 1 || 2 || 3   
	int 				lbl_size; //label size ===> 2 or 4


	int 				codage;

	int 				args[3][2]; // 0 - for codage T_REG r 01 T_DIR % 10 T_IND 11 /// 1 - distance 
	int 				bytes_above_i; // in label length 



	int 				has_codage;
	int 				c_len;//byte length of the instruction

	struct s_t			*next;

}						t_t;


typedef struct 				s_lable
{
	t_t						*instruct; //
	char 					*label_name;
	struct s_lable			*next;
	struct s_lable			*prev;
	int 					lbl_len; //length of lable
	int 					bytes_above;
	//int 					bytes_below; 
}							t_lable;


typedef struct	s_binfile
{
	int				fd;//incoming file
	int 			fd_file_out;//resulting file
	unsigned char	a[4];

	char 			*f_contents;//a buf where all the data is stored written as a single line

	int				flag_a;//flag a
	char			*arg_name;//string argv[i]



	unsigned int 	arg_length; //file length
	unsigned int 	file_length; // my file length 


	char 			*name;			
	char 			*comment;
	unsigned int	champ_size_nbr;//


	char			magic_start[4];
	char 			champ_name[PROG_NAME_LENGTH + 1];
	char 			champ_comment[COMMENT_LENGTH + 1];
	char 			champ_size[4];



	char 			*exec_code;//executable code
	t_lable			*labels_list;


	
}				t_binfile;




//********************************* LIST FUNCTIONS *********************



void	label_distance(t_binfile 	*bin);

//********************************* PRINTING FUNCTIONS******************

void			ft_print_usage();
void	 		ft_print_inv_f();
void			ft_print_flag_a(t_binfile *bin);
void			ft_print_inv_input();




//********************************* ENCODING FUNCTIONS******************


void			fill_magic_start(t_binfile *bin);
int				fill_name_comment(t_binfile *bin);


//**********************************FILE FUNCTIONS****************
void			create_cor_file(t_binfile *bin); 
void			fill_corfile_contents(t_binfile *bin);



void		skip_name_comment(size_t	*count,  char (*contents)[]);

void		ft_zero_what_left(t_binfile *bin, size_t	*count,  char (*contents)[]);

void		clean_name_comment(t_binfile *bin, char (*contents)[]);




void		fill_corfile_contents(t_binfile *bin);
void 		parse_file(t_binfile *bin, char (*contents)[]);

//********************************* FREEEING FUNCTIONS******************
void			ft_clean_parse(char **parse);//strdel char * array 



int			parse_commands(t_binfile *file);
int			ft_cmd_arguments(char	*c_name);

int			ft_cmd_lbls(char	*c_name);
int			has_codage(char	*c_name);

//********************************* VALIDATION FUNCTIONS******************

char		*label_name_is_valid(t_binfile *file, char *str);
int			arguments_validator(t_binfile *file, t_t *token, char *arg, int i);

#endif