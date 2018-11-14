#include "../corewar.h"

void create_map(header_t bots[4], t_flags *params)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	static unsigned char map[MEM_SIZE];

	i = 0;
	j = 0;
	k = 0;
	ft_bzero(map, MEM_SIZE);
	while (i < MEM_SIZE && j < (*params).bots_quantity)
	{
		if (i == bots[j].start_index)
		{
			k = 0;
			while (k < bots[j].prog_size)
			{
				map[i] = bots[j].exec_part[k];
				i++;
				k++;
			}
			j++;
		}
		i++;
	}
	/*i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 128 == 0)
			ft_printf("\n");
		ft_printf("%.2x ", map[i]);
		i++;
	}*/
	vm_cycle(map, params, bots);
}

int read_bots(t_flags *params)
{
	unsigned int 		i;
	int j;
	int 		fd;
	static header_t bots[4];
	unsigned int len;
	unsigned int	size;
	unsigned int	buf;
	unsigned char *str;

	i = 0;
	j = 0;
	fd = 0;
	init_bots(bots);
	while ((*params).players[j] != NULL)
	{
		i = 0;
		fd = open((*params).players[j], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("%s %s\n", "Can't read source file", (*params).players[j]);
			return (0);
		}
		len = (int)lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET);
		str = (unsigned char *)malloc(sizeof(unsigned char) * len + 1);
		read(fd, str, len);
		//str[i] = '\0';
		/*while (i < len)
		{
			if (i % 64 == 0)
				ft_printf("\n");
			ft_printf("%.2x ", str[i]);
			i++;
		}*/
		ft_strncpy(bots[j].prog_name, (const char *)(&str[4]), PROG_NAME_LENGTH);
		size = 0;
		buf = 0;
		buf = str[136] << 24;
		size |= buf;
		buf = str[137] << 16;
		size |= buf;
		buf = str[138] << 8;
		size |= buf;
		size |= str[139];
		bots[j].prog_size = size;
		if (size > 682)
		{
			ft_printf("Error: %s has too large a code (%d bytes > 682 bytes)\n", (*params).players[j], size);
			ft_strdel((char **)(&str));
			return (0);
		}
		ft_strncpy(bots[j].comment, (const char *)(&str[140]), COMMENT_LENGTH);
		bots[j].exec_part = (unsigned char *)malloc(sizeof(unsigned char) * (bots[j].prog_size + 1));
		ft_bzero(bots[j].exec_part, bots[j].prog_size + 1);
		//ft_strncpy((char *)(bots[j].exec_part), (const char *)(&str[2192]), bots[j].prog_size); ?why in cycle and not in strncpy
		//ft_printf("\n%s\n", bots[j].prog_name);
		//ft_printf("%d\n", bots[j].prog_size);
		//ft_printf("%s\n", bots[j].comment);
		bots[j].start_index = (MEM_SIZE / (*params).bots_quantity) * j;
		i = 0;
		while (i < bots[j].prog_size)
		{
			bots[j].exec_part[i] = str[2192 + i];
			/*if (i % 64 == 0)
				ft_printf("\n");
			ft_printf("%.2x ", bots[j].exec_part[i]);*/
			i++;
		}
		ft_strdel((char **)(&str));
		//ft_printf("\n");
		j++;
	}
	create_map(bots, params);
	return (1);
}

void print_usage(void)
{
	char *octos;

	octos = "##########################################################";
	ft_printf("%s", "Usage: ./corewar [-d N -s N -v N | -b --stealth ");
	ft_printf("%s\n", "| -n --stealth] [-a] <champion1.cor> <...>");
	ft_printf("%6s", "-a");
	ft_printf("%58s\n", ": Prints output from \"aff\" (Default is to hide it)");
	ft_printf("%s%s\n", "#### TEXT OUTPUT MODE ", octos);
	ft_printf("%8s%46s\n", "-d N", ": Dumps memory after N cycles then exits");
	ft_printf("%8s", "-s N");
	ft_printf("%57s\n", ": Runs N cycles, dumps memory, pauses, then repeats");
	ft_printf("%26s", "-v N      : Verbosity ");
	ft_printf("%s\n", "levels, can be added together to enable several");
	ft_printf("%43s%32s\n", "- 0 : Show only essentials\n", "- 1 : Show lives");
	ft_printf("%33s\n", "- 2 : Show cycles");
	ft_printf("%67s\n", "- 4 : Show operations (Params are NOT litteral ...)");
	ft_printf("%33s\n", "- 8 : Show deaths");
	ft_printf("%59s\n", "- 16 : Show PC movements (Except for jumps)");
	ft_printf("%s%s\n", "#### BINARY OUTPUT MODE ", octos);
	ft_printf("%52s\n", "-b        : Binary output mode for corewar.42.fr");
	ft_printf("%53s\n", "--stealth : Hides the real contents of the memory");
	ft_printf("%s%s\n", "#### NCURSES OUTPUT MODE ", octos);
	ft_printf("%35s\n", "-n        : Ncurses output mode");
	ft_printf("%53s\n", "--stealth : Hides the real contents of the memory");
	ft_printf("%s%.22s\n", octos, octos);
}

int check_flags_core(int argc, char **argv, t_flags *params)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-a") == 0)
			(*params).a_aff = 1;
		else if (ft_strcmp(argv[i], "-d") == 0)
		{
			(*params).d_dumps_memory = ft_atoi(argv[i + 1]);
			i += 2;
			continue ;
		}
		else if (ft_strcmp(argv[i], "-s") == 0)
		{
			(*params).s_cycles = ft_atoi(argv[i + 1]);
			i += 2;
			continue ;
		}
		else if (ft_strcmp(argv[i], "-v") == 0)
		{
			(*params).v_verbosity = ft_atoi(argv[i + 1]);
			i += 2;
			continue ;
		}
		else if (ft_strcmp(argv[i], "-b") == 0)
			(*params).binary = 1;
		else if (ft_strcmp(argv[i], "---stealth") == 0 && ft_strcmp(argv[i - 1], "-b"))
			(*params).b_stealth = 1;
		else if (ft_strcmp(argv[i], "-nc") == 0)
			(*params).ncurses = 1;
		else if (ft_strcmp(argv[i], "---stealth") == 0 && ft_strcmp(argv[i - 1], "-n"))
			(*params).n_stealth = 1;
		else if (ft_strchr(argv[i], '.') && ft_strcmp(&(argv[i][ft_strlen(argv[i]) - 4]), ".cor") == 0)
		{
			if ((*params).bots_quantity == 4)
			{
				ft_printf("%s\n", "Too many champions");
				return (0);
			}
			(*params).players[(*params).bots_quantity] = argv[i];
			(*params).bots_quantity++;
		}
		else
		{
			ft_printf("%s %s\n", "Can't read source file", argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_flags params;
	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	params_init(&params);
	if (!check_flags_core(argc, argv, &params))
		exit(0);
	/*ft_printf("%d\n", params.a_aff);
	ft_printf("%d\n", params.d_dumps_memory);
	ft_printf("%d\n", params.s_cycles);
	ft_printf("%d\n", params.v_verbosity);
	ft_printf("%d\n", params.binary);
	ft_printf("%d\n", params.b_stealth);
	ft_printf("%d\n", params.ncurses);
	ft_printf("%d\n", params.n_stealth);
	ft_printf("%s\n", params.players[0]);
	ft_printf("%s\n", params.players[1]);
	ft_printf("%s\n", params.players[2]);
	ft_printf("%s\n", params.players[3]);*/
	if (!read_bots(&params))
		exit(0);
}