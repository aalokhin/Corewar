#include "corewar.h"

void load(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	if((*tmp).argv[1][0] != REG_CODE || (*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16 || (*tmp).argv[2][0])
		return ;
	if ((*tmp).argv[0][0] == DIR_CODE) //t_reg -> index of n array
	{
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		else
			(*tmp).carry = 0;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
	}
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		(*tmp).argv[0][1] %= IDX_MOD;
		i = (*tmp).current_position + (*tmp).argv[0][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		if (((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]) == 0)
			(*tmp).carry = 1;
		else
			(*tmp).carry = 0;
		(*tmp).regs[(*tmp).argv[1][1] - 1] =
		(map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];

	}
	ft_printf("%s\n", "test_load");
}

void store(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16 || (*tmp).argv[2][0])
		return ;
	if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).current_position + ((*tmp).argv[1][1] % IDX_MOD);
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		map[i] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0xff);
		map[i + 1] = (((*tmp).regs[(*tmp).argv[0][1] - 1] >> 8) & 0xff);
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
	}
	else if ((*tmp).argv[1][0] == REG_CODE && (*tmp).argv[1][1] >= 1 && (*tmp).argv[1][1] <= 16)
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1];
	ft_printf("%s\n", "store_test");
}

void addition(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] != REG_CODE)
		return ;
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return ;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] + (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	else
		(*tmp).carry = 0;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] +
	(*tmp).regs[(*tmp).argv[1][1] - 1];	
	ft_printf("%s\n", "tets_addition");
	map[0] = map[0];
}

void substraction(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] != REG_CODE)
		return ;
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return ;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] - (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	else
		(*tmp).carry = 0;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] -
	(*tmp).regs[(*tmp).argv[1][1] - 1];	
	ft_printf("%s\n", "tets_SUSCTRACTION");
	map[0] = map[0];
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
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
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
		(*tmp).argv[0][1] %= IDX_MOD;
		i = (*tmp).current_position + (*tmp).argv[0][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		(*tmp).argv[1][1] %= IDX_MOD;
		i = (*tmp).current_position + (*tmp).argv[1][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}

	if ((one & two) == 0)
		(*tmp).carry = 1;
	else
		(*tmp).carry = 0;
	(*tmp).argv[2][1] = one & two;
	ft_printf("%s\n", "TESE->BIT->AND");
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
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
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
		(*tmp).argv[0][1] %= IDX_MOD;
		i = (*tmp).current_position + (*tmp).argv[0][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		(*tmp).argv[1][1] %= IDX_MOD;
		i = (*tmp).current_position + (*tmp).argv[1][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}

	if ((one | two) == 0)
		(*tmp).carry = 1;
	else
		(*tmp).carry = 0;
	(*tmp).argv[2][1] = one | two;
	ft_printf("%s\n", "TESE->BIT->OR");
	map[0] = map[0];
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
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
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
		(*tmp).argv[0][1] %= IDX_MOD;
		i = (*tmp).current_position + (*tmp).argv[0][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		one = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		(*tmp).argv[1][1] %= IDX_MOD;
		i = (*tmp).current_position + (*tmp).argv[1][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = ((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]);
	}

	if ((one ^ two) == 0)
		(*tmp).carry = 1;
	else
		(*tmp).carry = 0;
	(*tmp).argv[2][1] = one ^ two;
	ft_printf("%s\n", "TESE->BIT->XOR");
	map[0] = map[0];
}

void zjmp(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).carry == 1)
	{
		while (i < (*main_cycle).processes && i != cur_proc)
		{
			tmp = tmp->next;
			i++;
		}
		(*main_cycle).indexes[(*tmp).current_position][1] = 0;
		(*tmp).current_position += ((*tmp).argv[0][1] % IDX_MOD);
		if ((*tmp).current_position < 0 || (*tmp).current_position >= MEM_SIZE)
			(*tmp).current_position %= MEM_SIZE;
		if ((*tmp).parent_nbr == -1)
			(*main_cycle).indexes[(*tmp).current_position][0] = cur_proc + 1;
		else
			(*main_cycle).indexes[(*tmp).current_position][0] = (*tmp).parent_nbr + 1;
		(*main_cycle).indexes[(*tmp).current_position][1] = 1;
	}
	ft_printf("%s\n", "test zjmp");
	map[0] = map[0];
}
