#include "corewar.h"

void live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	int other_proc;
	t_proc *tmp;
	int arg_ind;
	t_proc *child_proc;
	
	i = 0;
	other_proc = 0;
	arg_ind = 0;
	tmp = head_proc;
	child_proc = NULL;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp)
	{
		(*tmp).if_live = 1;
		(*tmp).last_live_cycle = (*main_cycle).cycles;
	}
	child_proc = tmp;
	if ((*tmp).parent_nbr > -1)
	{
		tmp = head_proc;
		i = 0;
		other_proc = (*tmp).parent_nbr;
		while (i < (*main_cycle).processes && i != other_proc)
		{
			tmp = tmp->next;
			i++;
		}
		(*tmp).child_proc_lives++;
	}
	arg_ind = find_arg_index(tmp, DIR_CODE);
	if (arg_ind >= 0 && arg_ind < 3 && (*child_proc).argv[arg_ind][0] &&
		(*child_proc).argv[arg_ind][1] < (*main_cycle).processes)
	{
		i = 0;
		other_proc = (*tmp).argv[arg_ind][1];
		tmp = head_proc;
		while (tmp && i != other_proc)
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp)
		{
			(*tmp).if_live = 1;
			(*tmp).last_live_cycle = (*main_cycle).cycles;
		}
		
		if (tmp && (*tmp).parent_nbr > -1)
		{
			tmp = head_proc;
			i = 0;
			other_proc = (*tmp).parent_nbr;
			while (i < (*main_cycle).processes && i != other_proc)
			{
				tmp = tmp->next;
				i++;
			}
			if (tmp)
				(*tmp).child_proc_lives++;
		}
	}
	ft_printf("%s\n", "test live");
	map[0] = map[0];
}


void load_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	if ((*processes).argv[0][0] == IND_CODE)
	{
		arg_ind = find_arg_index(processes, IND_CODE);
		i = ((*processes).argv[arg_ind][1] % IDX_MOD) + (*processes).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		(*processes).argv[0][1] = (map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];
	}
	i = (((*processes).argv[0][1] + (*processes).argv[1][1]) % IDX_MOD) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	(*processes).argv[2][1] = (map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];
	ft_printf("%s\n", "test load_ind");
}

void store_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	if ((*processes).argv[1][0] == IND_CODE)
	{
		i = (*processes).argv[1][1] % IDX_MOD;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		(*processes).argv[1][1] = (map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];
	}
	i = (((*processes).argv[1][1] + (*processes).argv[2][1]) % IDX_MOD) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	map[i] = (*processes).argv[0][1];
	if ((*processes).parent_nbr == -1)
		(*main_cycle).indexes[i][0] = cur_proc;
	else
		(*main_cycle).indexes[i][0] = (*processes).parent_nbr;
 	ft_printf("%s\n", "test_sti");
}

void ffork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	arg_ind = find_arg_index(processes, DIR_CODE);
	i = ((*processes).argv[arg_ind][1] % IDX_MOD) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	processes_add(processes, map, main_cycle, i);
	ft_printf("%s\n", "test_>fork");
}

void lload(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	ft_printf("%s\n", "test_load load");
}

void lload_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	if ((*processes).argv[1][0] == IND_CODE)
	{
		i = (*processes).argv[1][1] % IDX_MOD;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		(*processes).argv[1][1] = (map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];
	}
	i = (((*processes).argv[1][1] + (*processes).argv[2][1])) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	map[i] = (*processes).argv[0][1];
	if ((*processes).parent_nbr == -1)
		(*main_cycle).indexes[i][0] = cur_proc;
	else
		(*main_cycle).indexes[i][0] = (*processes).parent_nbr;
	ft_printf("%s\n", "test_load lload_ind");
}

void long_fork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	arg_ind = find_arg_index(processes, DIR_CODE);
	i = ((*processes).argv[arg_ind][1]) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	processes_add(processes, map, main_cycle, i);
	ft_printf("%s\n", "long->fork");
}

void aff(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	// надо узнать куда печатать символ и правильно прописать функцию
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	ft_printf("%s\n", "aff -> test");
	ft_printf("%c\n", ((*processes).argv[0][1] % 256));
	map[0] = map[0];
}