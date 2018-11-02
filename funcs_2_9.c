#include "corewar.h"

void load(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	int arg_ind;

	i = 0;
	arg_ind = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	arg_ind = find_arg_index(processes, REG_CODE);
	if ((*processes).argv[0][0] == DIR_CODE) //t_reg -> index of n array
	{
		if ((*processes).argv[arg_ind][1] >= 0 && (*processes).argv[arg_ind][1] < 16)
		{
			if ((*processes).argv[0][1] == 0)
				(*processes).carry = 1;
			else
				(*processes).carry = 0;
			(*processes).regs[(*processes).argv[arg_ind][1]] = (*processes).argv[0][1];
		}
	}
	else if ((*processes).argv[0][0] == IND_CODE)
	{
		(*processes).argv[0][1] %= IDX_MOD;
		i = (*processes).current_position + (*processes).argv[0][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		if (((map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i]) == 0)
			(*processes).carry = 1;
		else
			(*processes).carry = 0;
		if ((*processes).argv[arg_ind][1] >= 0 && (*processes).argv[arg_ind][1] < 16)
		(*processes).regs[(*processes).argv[arg_ind][1]] =
		(map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];

	}
	ft_printf("%s\n", "test_load");
}

void store(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if ((*processes).argv[1][0] == IND_CODE)
	{
		i = (*processes).current_position + ((*processes).argv[1][1] % IDX_MOD);
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		if ((*processes).argv[0][1] >= 0 && (*processes).argv[0][1] < 16)
			map[i] = (*processes).regs[(*processes).argv[0][1]];
		(*main_cycle).indexes[i][0] = cur_proc;
	}
	else if ((*processes).argv[1][0] == REG_CODE)
		(*processes).regs[(*processes).argv[1][1]] = (*processes).argv[0][1];
	ft_printf("%s\n", "store_test");
}

void addition(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if (((*processes).argv[0][1] + (*processes).argv[1][1]) == 0)
		(*processes).carry = 1;
	else
		(*processes).carry = 0;
	(*processes).argv[2][1] = (*processes).argv[0][1] + (*processes).argv[1][1];	
	ft_printf("%s\n", "tets_addition");
	map[0] = map[0];
}

void substraction(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if (((*processes).argv[0][1] - (*processes).argv[1][1]) == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	(*processes).argv[2][1] = (*processes).argv[0][1] - (*processes).argv[1][1];	
	ft_printf("%s\n", "tets_SUSCTRACTION");
	map[0] = map[0];
}

void bit_and(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if (((*processes).argv[0][1] & (*processes).argv[1][1]) == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	(*processes).argv[2][1] = (*processes).argv[0][1] & (*processes).argv[1][1];
	ft_printf("%s\n", "TESE->BIT->AND");
	map[0] = map[0];
}

void bit_or(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if (((*processes).argv[0][1] | (*processes).argv[1][1]) == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	(*processes).argv[2][1] = (*processes).argv[0][1] | (*processes).argv[1][1];	
	ft_printf("%s\n", "TESE->BIT->OR");
	map[0] = map[0];
}

void bit_xor(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if (((*processes).argv[0][1] ^ (*processes).argv[1][1]) == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	(*processes).argv[2][1] = (*processes).argv[0][1] ^ (*processes).argv[1][1];	
	ft_printf("%s\n", "TESE->BIT->XOR");
	map[0] = map[0];
}

void zjmp(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	int arg_ind;

	i = 0;
	arg_ind = 0;	
	if ((*processes).carry == 1)
	{
		while (i < (*main_cycle).processes && i != cur_proc)
		{
			processes = processes->next;
			i++;
		}
		arg_ind = find_arg_index(processes, DIR_CODE);
		(*processes).current_position = ((*processes).argv[arg_ind][1] % IDX_MOD);
		if ((*processes).current_position < 0 || (*processes).current_position >= MEM_SIZE)
			(*processes).current_position %= MEM_SIZE;
		if ((*processes).parent_nbr == -1)
			(*main_cycle).indexes[(*processes).current_position][0] = cur_proc;
		else
			(*main_cycle).indexes[(*processes).current_position][0] = (*processes).parent_nbr;
		(*main_cycle).indexes[(*processes).current_position][1] = 1;
	}
	ft_printf("%s\n", "test zjmp");
	map[0] = map[0];
}
