
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
	int				flag_a;
	char			*arg_name;
	unsigned int 	arg_length;


	char			magic_start[4];

	char 			champ_name[PROG_NAME_LENGTH + 1];
	char 			*name;			

	char 			champ_comment[COMMENT_LENGTH + 1];
	char 			*comment;

	char 			champ_size[4];
	unsigned int	champ_size_nbr;


	char 			*exec_code;

	
}				t_binfile;

					

//********************************* PRINTING FUNCTIONS******************

void			ft_print_usage();
void	 		ft_print_inv_f();
void			ft_print_flag_a(t_binfile *bin);

#endif