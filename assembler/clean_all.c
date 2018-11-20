#include "asm.h"

void		ft_clean_all(t_binfile	*bin)
{
	ft_strdel(&((*bin).f_contents));
	ft_strdel(&((*bin).copy)); 
	ft_strdel(&((*bin).arg_name)); 
	ft_strdel(&((*bin).res_arg_name)); 
	ft_strdel(&((*bin).name)); 
	ft_strdel(&((*bin).comment)); 

}