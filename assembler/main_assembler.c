#include "asm.h"

int main(int argc, char **argv)
{
	/* code */
	if (argc == 1)
	{
		ft_printf("sorry!");
	}
	argv[1] = argv[1];
	ft_printf("hi ib assembler\n");
	return 0;
}