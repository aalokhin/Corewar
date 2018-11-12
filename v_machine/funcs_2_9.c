#include "../corewar.h"

int load(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if((*tmp).argv[1][0] != REG_CODE || (*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16 || (*tmp).argv[2][0])
		return (0);
	(*tmp).carry = 0;
	if ((*tmp).argv[0][0] == DIR_CODE) //t_reg -> index of n array
	{
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
		ft_printf("P%5d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
		return (1);
	}
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		(*tmp).argv[0][1] = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]);
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
		ft_printf("P%5d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
		return (1);
	}
	return (0);
	(*main_cycle).cycles = (*main_cycle).cycles;
}

int store(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16 || (*tmp).argv[2][0])
		return (0);
	if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[1][1] % IDX_MOD;
		ft_printf("P%5d | st r%d %d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
		i = (i + MEM_SIZE) % MEM_SIZE;
		map[(i + MEM_SIZE + 3) % MEM_SIZE] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x000000FF); 
		map[(i + MEM_SIZE + 2) % MEM_SIZE] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x0000FF00) >> 8; 
		map[(i + MEM_SIZE + 1) % MEM_SIZE] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x00FF0000) >> 16; 
		map[i] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0xFF000000) >> 24;
		if ((*tmp).parent_nbr == -1)
		{
			(*main_cycle).indexes[i][0] = cur_proc + 1;
			(*main_cycle).indexes[(i + MEM_SIZE + 1) % MEM_SIZE][0] = cur_proc + 1;
			(*main_cycle).indexes[(i + MEM_SIZE + 2) % MEM_SIZE][0] = cur_proc + 1;
			(*main_cycle).indexes[(i + MEM_SIZE + 3) % MEM_SIZE][0] = cur_proc + 1;
		}
		else
		{
			(*main_cycle).indexes[i][0] = (*tmp).parent_nbr + 1;
			(*main_cycle).indexes[(i + MEM_SIZE + 1) % MEM_SIZE][0] = (*tmp).parent_nbr + 1;
			(*main_cycle).indexes[(i + MEM_SIZE + 2) % MEM_SIZE][0] = (*tmp).parent_nbr + 1;
			(*main_cycle).indexes[(i + MEM_SIZE + 3) % MEM_SIZE][0] = (*tmp).parent_nbr + 1;
		}
		return (1);
	}
	else if ((*tmp).argv[1][0] == REG_CODE && (*tmp).argv[1][1] >= 1 && (*tmp).argv[1][1] <= 16)
	{
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1];
		ft_printf("P%5d | st r%d %d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
		return (1);
	}
	return (0);
}

int addition(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] != REG_CODE)
		return (0);
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return (0);
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] + (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] +
	(*tmp).regs[(*tmp).argv[1][1] - 1];	
	ft_printf("P%5d | add r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int substraction(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] != REG_CODE)
		return (0);
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return (0);
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] - (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] -
	(*tmp).regs[(*tmp).argv[1][1] - 1];	
	ft_printf("P%5d | sub r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int bit_and(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	unsigned int one;
	unsigned int two;
	t_proc *tmp;

	i = 0;
	one = 0;
	two = 0;
	tmp = processes;
	if ((*tmp).argv[2][0] != REG_CODE || (*tmp).argv[2][1] < 1 || (*tmp).argv[2][1] > 16)
		return (0);
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return (0);

	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[1][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]);
	}
	(*tmp).carry = 0;
	if ((one & two) == 0)
		(*tmp).carry = 1;	
	(*tmp).regs[(*tmp).argv[2][1] - 1] = one & two;
	ft_printf("P%5d | and %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int bit_or(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	unsigned int one;
	unsigned int two;
	t_proc *tmp;

	i = 0;
	one = 0;
	two = 0;
	tmp = processes;
	if ((*tmp).argv[2][0] != REG_CODE || (*tmp).argv[2][1] < 1 || (*tmp).argv[2][1] > 16)
		return (0);
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return (0);

	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[1][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]);
	}
	(*tmp).carry = 0;
	if ((one | two) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = one | two;
	ft_printf("P%5d | or %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int bit_xor(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	unsigned int one;
	unsigned int two;
	t_proc *tmp;

	i = 0;
	one = 0;
	two = 0;
	tmp = processes;
	if ((*tmp).argv[2][0] != REG_CODE || (*tmp).argv[2][1] < 1 || (*tmp).argv[2][1] > 16)
		return (0);
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return (0);

	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[1][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]);
	}
	(*tmp).carry = 0;
	if ((one ^ two) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = one ^ two;
	ft_printf("P%5d | xor %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int zjmp(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;
	char *res;

	i = 0;
	res = "FAILED";
	tmp = processes;
	if ((*tmp).carry == 1)
	{
		(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][1] = 0;
		(*tmp).current_position += ((*tmp).argv[0][1] % IDX_MOD);
		(*tmp).current_position = ((*tmp).current_position + MEM_SIZE) % MEM_SIZE;
		if ((*tmp).parent_nbr == -1)
			(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][0] = cur_proc + 1;
		else
			(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][0] = (*tmp).parent_nbr + 1;
		(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][1] = 1;
		res = "OK";
	}
	ft_printf("P%5d | zjmp %d %s\n", cur_proc + 1, (*tmp).argv[0][1], res);
	map[0] = map[0];
	return (1);
}