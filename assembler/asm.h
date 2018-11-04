
#ifndef __ASM_H
# define __ASM_H

# include <fcntl.h>          
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../op.h"

#include <stdio.h>



typedef struct	s_binfile
{
	int				fd;//incoming file
	int 			fd_file_out;//resulting file

	char 			*f_contents;//a buf where all the data is stored written as a single line

	int				flag_a;//flag a
	char			*arg_name;//string argv[i]



	unsigned int 	arg_length; //file length


	char 			*name;			
	char 			*comment;
	unsigned int	champ_size_nbr;//


	char			magic_start[4];
	char 			champ_name[PROG_NAME_LENGTH + 1];
	char 			champ_comment[COMMENT_LENGTH + 1];
	char 			champ_size[4];



	char 			*exec_code;//executable code

	
}				t_binfile;

					

//********************************* PRINTING FUNCTIONS******************

void			ft_print_usage();
void	 		ft_print_inv_f();
void			ft_print_flag_a(t_binfile *bin);
void			ft_print_inv_input();




//********************************* ENCODING FUNCTIONS******************


void			fill_magic_start(t_binfile *bin);
void			fill_name_comment(t_binfile *bin);



//**********************************FILE FUNCTIONS****************
void			create_cor_file(t_binfile *bin); 
void			fill_corfile_contents(t_binfile *bin);



void		skip_name_comment(size_t	*count,  char (*contents)[]);

void		ft_zero_what_left(t_binfile *bin, size_t	*count,  char (*contents)[]);

void		clean_name_comment(t_binfile *bin, char (*contents)[]);




void		fill_corfile_contents(t_binfile *bin);
void 		parse_file(t_binfile *bin, char (*contents)[]);

//********************************* FREEEING FUNCTIONS******************

#endif