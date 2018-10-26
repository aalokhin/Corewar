#include "corewar.h"

void load(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;
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
		(*processes).regs[(*processes).argv[arg_ind][1]] = (*processes).argv[0][1];
	}
	else if ((*processes).argv[0][0] == IND_CODE)
	{

		(*processes).argv[0][1] = (*processes).argv[0][1] % IDX_MOD;
		i = (*processes).current_position + (*processes).argv[0][1];
		

		(*processes).regs[(*processes).argv[arg_ind][1]] =
		(map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];

	}
	if ((*processes).regs[(*processes).argv[arg_ind][1]] == 0)
		(*processes).carry = 1;
	else
		(*processes).carry = 0;
	ft_printf("%s\n", "test_load");
	map[0] = map[0];
}

void store(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if ((*processes).argv[1][0] == IND_CODE)
	{
		map[(*processes).current_position + (*processes).argv[1][1] % IDX_MOD] =
		(*processes).regs[(*processes).argv[1][1]];
	}
	else if ((*processes).argv[1][0] == REG_CODE)
		(*processes).regs[(*processes).argv[1][1]] = (*processes).argv[0][1];

	ft_printf("%s\n", "store_test");

	map[0] = map[0];
}

void addition(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	(*processes).argv[2][1] = (*processes).argv[0][1] + (*processes).argv[1][1];

	if ((*processes).argv[2][1] == 0)
		(*processes).carry = 1;
	else
		(*processes).carry = 0;
	ft_printf("%s\n", "tets_addition");

	map[0] = map[0];
}

void substraction(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	(*processes).argv[2][1] = (*processes).argv[0][1] - (*processes).argv[1][1];

	if ((*processes).argv[2][1] == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	ft_printf("%s\n", "tets_SUSCTRACTION");

	map[0] = map[0];
}

void bit_and(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	(*processes).argv[2][1] = (*processes).argv[0][1] & (*processes).argv[1][1];

	if ((*processes).argv[2][1] == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	ft_printf("%s\n", "TESE->BIT->AND");

	map[0] = map[0];
}

void bit_or(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	(*processes).argv[2][1] = (*processes).argv[0][1] | (*processes).argv[1][1];

	if ((*processes).argv[2][1] == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	ft_printf("%s\n", "TESE->BIT->OR");

	map[0] = map[0];
}

void bit_xor(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	(*processes).argv[2][1] = (*processes).argv[0][1] ^ (*processes).argv[1][1];

	if ((*processes).argv[2][1] == 0)
			(*processes).carry = 1;
	else
		(*processes).carry = 0;
	
	ft_printf("%s\n", "TESE->BIT->XOR");

	map[0] = map[0];
}

void zjmp(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;
	int arg_ind;


	i = 0;
	arg_ind = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	arg_ind = find_arg_index(processes, DIR_CODE);
	if ((*processes).carry == 1)
	{
		(*processes).current_position = (*processes).argv[arg_ind][1] % IDX_MOD;
	}

	ft_printf("%s\n", "test zjmp");

	map[0] = map[0];
}
