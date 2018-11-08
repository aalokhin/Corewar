#include "corewar.h"

void load(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if((*tmp).argv[1][0] != REG_CODE || (*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16 || (*tmp).argv[2][0])
		return ;
	(*tmp).carry = 0;
	if ((*tmp).argv[0][0] == DIR_CODE) //t_reg -> index of n array
	{
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
		ft_printf("P%5d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
	}
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
		(*tmp).argv[0][1] = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
		ft_printf("P%5d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
	}
	(*main_cycle).cycles = (*main_cycle).cycles;
}

void store(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16 || (*tmp).argv[2][0])
		return ;
	if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[1][1] % IDX_MOD;
		map[i + 1] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0xff);
		map[i] = (((*tmp).regs[(*tmp).argv[0][1] - 1] >> 8) & 0xff);
		if ((*tmp).parent_nbr == -1)
		{
			(*main_cycle).indexes[i][0] = cur_proc + 1;
			(*main_cycle).indexes[i + 1][0] = cur_proc + 1;
		}
		else
		{
			(*main_cycle).indexes[i][0] = (*tmp).parent_nbr + 1;
			(*main_cycle).indexes[i + 1][0] = (*tmp).parent_nbr + 1;
		}
		ft_printf("P%5d | st r%d %d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
	}
	else if ((*tmp).argv[1][0] == REG_CODE && (*tmp).argv[1][1] >= 1 && (*tmp).argv[1][1] <= 16)
	{
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1];
		ft_printf("P%5d | st r%d %d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
	}
}

void addition(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] != REG_CODE)
		return ;
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return ;
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] + (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] +
	(*tmp).regs[(*tmp).argv[1][1] - 1];	
	ft_printf("P%5d | add r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
	(*main_cycle).cycles = (*main_cycle).cycles;
}

void substraction(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] != REG_CODE)
		return ;
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return ;
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] - (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] -
	(*tmp).regs[(*tmp).argv[1][1] - 1];	
	ft_printf("P%5d | sub r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
	(*main_cycle).cycles = (*main_cycle).cycles;
}

void bit_and(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
		return ;
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return ;
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return ;

	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = ((*tmp).current_position + (*tmp).argv[0][1]) % MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = ((*tmp).current_position + (*tmp).argv[1][1]) % MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	(*tmp).carry = 0;
	if ((one & two) == 0)
		(*tmp).carry = 1;	
	(*tmp).regs[(*tmp).argv[2][1] - 1] = one & two;
	ft_printf("P%5d | and %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
}

void bit_or(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
		return ;
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return ;
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return ;

	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = ((*tmp).current_position + (*tmp).argv[0][1]) % MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = ((*tmp).current_position + (*tmp).argv[1][1]) % MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	(*tmp).carry = 0;
	if ((one | two) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = one | two;
	ft_printf("P%5d | or %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
}

void bit_xor(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
		return ;
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return ;
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return ;

	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = ((*tmp).current_position + (*tmp).argv[0][1]) % MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = ((*tmp).current_position + (*tmp).argv[1][1]) % MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	(*tmp).carry = 0;
	if ((one ^ two) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = one ^ two;
	ft_printf("P%5d | xor %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
}

void zjmp(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;
	char *res;

	i = 0;
	res = "FAILED";
	tmp = processes;
	if ((*tmp).carry == 1)
	{
		(*main_cycle).indexes[(*tmp).current_position][1] = 0;
		(*tmp).argv[0][1] %= IDX_MOD;
		(*tmp).current_position = ((*tmp).current_position + (*tmp).argv[0][1] + MEM_SIZE) % MEM_SIZE;
		if ((*tmp).current_position < 0 || (*tmp).current_position >= MEM_SIZE)
			(*tmp).current_position %= MEM_SIZE;
		if ((*tmp).parent_nbr == -1)
			(*main_cycle).indexes[(*tmp).current_position][0] = cur_proc + 1;
		else
			(*main_cycle).indexes[(*tmp).current_position][0] = (*tmp).parent_nbr + 1;
		(*main_cycle).indexes[(*tmp).current_position][1] = 1;
		res = "OK";
	}
	ft_printf("P%5d | zjmp %d %s\n", cur_proc + 1, (*tmp).argv[0][1], res);
	map[0] = map[0];
}
