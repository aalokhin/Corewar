
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
	int				fd;
	int 			fd_file_out;

	int				flag_a;
	char			*arg_name;//argv[i]



	unsigned int 	arg_length; //file length


	char 			*name;			
	char 			*comment;
	unsigned int	champ_size_nbr;


	char			magic_start[4];
	char 			champ_name[PROG_NAME_LENGTH + 1];
	char 			champ_comment[COMMENT_LENGTH + 1];
	char 			champ_size[4];



	char 			*exec_code;

	
}				t_binfile;

					

//********************************* PRINTING FUNCTIONS******************

void			ft_print_usage();
void	 		ft_print_inv_f();
void			ft_print_flag_a(t_binfile *bin);
void			ft_print_inv_input();




//********************************* ENCODING FUNCTIONS******************


void			fill_magic_start(t_binfile *bin);



//**********************************FILE FUNCTIONS****************
void			create_cor_file(t_binfile *bin); 
void			fill_corfile_contents(t_binfile *bin);

//********************************* FREEEING FUNCTIONS******************

#endif