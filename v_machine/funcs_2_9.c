#include "../corewar.h"

int load(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if((*tmp).argv[1][0] != REG_CODE || (*tmp).argv[2][0] ||
		((*tmp).argv[0][0] != DIR_CODE && (*tmp).argv[0][0] != IND_CODE))
		return (0);
	else if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return (1);
	(*tmp).carry = 0;
	if ((*tmp).argv[0][0] == DIR_CODE)
	{
		if ((*tmp).argv[0][1] == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] = (*tmp).argv[0][1];
		if (((*main_cycle).verbose >> 2) & 1)
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
		if (((*main_cycle).verbose >> 2) & 1)
			ft_printf("P%5d | ld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
		return (1);
	}
	return (0);
	(*main_cycle).cycles = (*main_cycle).cycles;
}


int addition(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE
		|| (*tmp).argv[2][0] != REG_CODE)
		return (0);
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return (0);
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] + (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] +
	(*tmp).regs[(*tmp).argv[1][1] - 1];
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | add r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1],
		(*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int substraction(t_proc *processes, int cur_proc, t_cycle *main_cycle,
	unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[1][0] != REG_CODE ||
		(*tmp).argv[2][0] != REG_CODE)
		return (0);
	if ((*tmp).argv[0][1] < 0 || (*tmp).argv[0][1] > 16 || (*tmp).argv[1][1] < 0 ||
		(*tmp).argv[1][1] > 16 || (*tmp).argv[2][1] < 0 || (*tmp).argv[2][1] > 16)
		return (0);
	(*tmp).carry = 0;
	if (((*tmp).regs[(*tmp).argv[0][1] - 1] - (*tmp).regs[(*tmp).argv[1][1] - 1]) == 0)
		(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (*tmp).regs[(*tmp).argv[0][1] - 1] -
	(*tmp).regs[(*tmp).argv[1][1] - 1];
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | sub r%d r%d r%d\n", cur_proc + 1, (*tmp).argv[0][1],
			(*tmp).argv[1][1], (*tmp).argv[2][1]);
	map[0] = map[0];
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
		(*main_cycle).indexes[(*tmp).current_position % MEM_SIZE][1] = 1;
		res = "OK";
	}
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | zjmp %d %s\n", cur_proc + 1, (*tmp).argv[0][1], res);
	map[0] = map[0];
	return (1);
}