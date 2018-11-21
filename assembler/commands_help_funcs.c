#include "asm.h"

int				ft_cmd_lbls(char *c_name)
{
	char		*lbls2[6] = {"zjmp", "ldi", "sti", "fork", "lldi", "lfork"};
	char		*lbls4[10] = {"live", "ld", "st", "add", "sub", "and", "or", "xor", "lld", "aff"};
	int			i;

	if (!c_name)
		return (0);
	i = -1;
	while (++i < 6)
	{
		if (ft_strcmp(lbls2[i], c_name) == 0)
			return (2);
	}
	i = -1;
	while (++i < 10)
	{
		if (ft_strcmp(lbls4[i], c_name) == 0)
			return (4);
	}
	return (0);
}
