#include "asm.h"



int			ft_cmd_arguments(char	*c_name)
{
	char		*args1[5] = {"aff", "fork", "zjmp", "live", "lfork"};
	char		*args2[3] = {"ld", "st", "lld"};
	char		*args3[8] = {"sti", "and", "add", "sub", "or", "xor", "ldi", "lldi"};
	int 	i;

	i = -1;
	// printf("okokokok\n");
	if (!c_name)
 		return(0) ;
	while(++i < 5)
	{
		if (ft_strcmp(args1[i], c_name) == 0)
			return(1);
	}
	i = -1;
	while(++i < 3)
	{
		if (ft_strcmp(args2[i], c_name) == 0)
			return(2);
	}
	i = -1;
	while(++i < 8)
	{
		if (ft_strcmp(args3[i], c_name) == 0)
			return(3);
	}
	return (0);
}

int			ft_cmd_lbls(char	*c_name)
{
	char		*lbls2[6] = {"zjmp", "ldi", "sti", "fork", "lldi", "lfork"};
 	char		*lbls4[10] = {"live", "ld", "st", "add", "sub", "and", "or", "xor", "lld", "aff"};
 	
 	int 	i;

 	if (!c_name)
 		return(0);

 	i = -1;
 	while(++i < 6)
 	{
 		if (ft_strcmp(lbls2[i], c_name) == 0)
 			return(2);
 	}
 	i = -1;
 	while(++i < 10)
 	{
 		if (ft_strcmp(lbls4[i], c_name) == 0)
 			return(4);
 	}
 	return (0);
}


int			has_codage(char	*c_name)
{
	char		*cod1[4] = {"fork", "zjmp", "live", "lfork"};
	int 		i;

	i = -1;
	if (!c_name)
 		return(0);
 	while(++i < 4)
 	{
 		if (ft_strcmp(cod1[i], c_name) == 0)
 			return(1);
 	}
 	return (0);


}


void			ft_clean_parse(char **parse)
{
	int i;

	i = 0;
	while (parse[i])
		ft_strdel(&parse[i++]);
	free(parse);
}