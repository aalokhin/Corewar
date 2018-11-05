#include "corewar.h"

void live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	int other_proc;
	t_proc *tmp;
	t_proc *child_proc;
	
	i = 0;
	other_proc = 0;
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
	if ((*child_proc).argv[0][0] &&
		(*child_proc).argv[0][1] < (*main_cycle).processes)
	{
		i = 0;
		other_proc = (*tmp).argv[0][1];
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
	unsigned int one;
	unsigned int two;

	i = 0;
	arg_ind = 0;
	one = 0;
	two = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if ((*processes).argv[2][0] != REG_CODE || (*processes).argv[2][1] < 1 || (*processes).argv[2][1] > 16)
		return ;
	if ((*processes).argv[0][0] == REG_CODE && ((*processes).argv[0][1] < 1 || (*processes).argv[0][1] > 16))
		return ;
	if ((*processes).argv[1][0] == REG_CODE && ((*processes).argv[1][1] < 1 || (*processes).argv[1][1] > 16))
		return ;
	if ((*processes).argv[1][0] != REG_CODE && (*processes).argv[1][0] != DIR_CODE)
		return ;
	if ((*processes).argv[0][0] == REG_CODE)
		one = (*processes).regs[(*processes).argv[0][1] - 1];
	else if ((*processes).argv[0][0] == DIR_CODE)
		one = (*processes).argv[0][1];
	else if ((*processes).argv[0][0] == IND_CODE)
	{
		i = ((*processes).argv[0][1] % IDX_MOD) + (*processes).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		one = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}
	if ((*processes).argv[1][0] == REG_CODE)
		two = (*processes).regs[(*processes).argv[1][1] - 1];
	else if ((*processes).argv[1][0] == DIR_CODE)
		two = (*processes).argv[1][1];
	else if ((*processes).argv[1][0] == IND_CODE)
	{
		i = ((*processes).argv[1][1] % IDX_MOD) + (*processes).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}

	i = ((one + two) % IDX_MOD) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	(*processes).regs[(*processes).argv[2][1] - 1] = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) +
	(map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	ft_printf("%s\n", "test load_ind");
}

void store_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	unsigned int two;
	unsigned int three;

	i = 0;
	two = 0;
	three = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if ((*processes).argv[0][0] != REG_CODE || (*processes).argv[0][1] < 1 || (*processes).argv[0][1] > 16)
		return ;
	if ((*processes).argv[2][0] != REG_CODE && (*processes).argv[2][0] != DIR_CODE)
		return ;
	if ((*processes).argv[1][0] == REG_CODE && ((*processes).argv[1][1] < 1 || (*processes).argv[1][1] > 16))
		return ;
	if ((*processes).argv[2][0] == REG_CODE && ((*processes).argv[2][1] < 1 || (*processes).argv[2][1] > 16))
		return ;
	if ((*processes).argv[1][0] == REG_CODE)
		two = (*processes).regs[(*processes).argv[1][1] - 1];
	else if ((*processes).argv[1][0] == DIR_CODE)
		two = (*processes).argv[1][1];
	else if ((*processes).argv[1][0] == IND_CODE)
	{
		i = ((*processes).argv[1][1]) % IDX_MOD;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}
	if ((*processes).argv[2][0] == REG_CODE)
		three = (*processes).regs[(*processes).argv[2][1] - 1];
	else if ((*processes).argv[2][0] == DIR_CODE)
		three = (*processes).argv[2][1];

	i = ((two + three) % IDX_MOD) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	map[i] = ((*processes).regs[(*processes).argv[0][1] - 1] & 0x000000FF); 
	map[i + 1] = ((*processes).regs[(*processes).argv[0][1] - 1] & 0x0000FF00) >> 8; 
	map[i + 2] = ((*processes).regs[(*processes).argv[0][1] - 1] & 0x00FF0000) >> 16; 
	map[i + 3] = ((*processes).regs[(*processes).argv[0][1] - 1] & 0xFF000000) >> 24;
	if ((*processes).parent_nbr == -1)
	{
		(*main_cycle).indexes[i][0] = cur_proc + 1;
		(*main_cycle).indexes[i + 1][0] = cur_proc + 1;
		(*main_cycle).indexes[i + 2][0] = cur_proc + 1;
		(*main_cycle).indexes[i + 3][0] = cur_proc + 1;
	}
	else
	{
		(*main_cycle).indexes[i][0] = (*processes).parent_nbr + 1;
		(*main_cycle).indexes[i + 1][0] = (*processes).parent_nbr + 1;
		(*main_cycle).indexes[i + 2][0] = (*processes).parent_nbr + 1;
		(*main_cycle).indexes[i + 3][0] = (*processes).parent_nbr + 1;
	}
 	ft_printf("%s\n", "test_sti");
}

void ffork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	i = ((*processes).argv[0][1] % IDX_MOD) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	processes_add(processes, map, main_cycle, i);
	ft_printf("%s\n", "test_>fork");
}

void lload(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if((*processes).argv[1][0] != REG_CODE || (*processes).argv[1][1] < 1 || (*processes).argv[1][1] > 16 || (*processes).argv[2][0])
		return ;
	if ((*processes).argv[0][0] == DIR_CODE) //t_reg -> index of n array
	{
		if ((*processes).argv[0][1] == 0)
			(*processes).carry = 1;
		else
			(*processes).carry = 0;
		(*processes).regs[(*processes).argv[1][1] - 1] = (*processes).argv[0][1];
	}
	else if ((*processes).argv[0][0] == IND_CODE)
	{
		i = (*processes).current_position + (*processes).argv[0][1];
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		if (((map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE]) == 0)
			(*processes).carry = 1;
		else
			(*processes).carry = 0;
		(*processes).regs[(*processes).argv[1][1] - 1] =
		(map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];

	}
	ft_printf("%s\n", "test_load load");
}

void lload_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	int arg_ind;
	unsigned int one;
	unsigned int two;

	i = 0;
	arg_ind = 0;
	one = 0;
	two = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if ((*processes).argv[2][0] != REG_CODE || (*processes).argv[2][1] < 1 || (*processes).argv[2][1] > 16)
		return ;
	if ((*processes).argv[0][0] == REG_CODE && ((*processes).argv[0][1] < 1 || (*processes).argv[0][1] > 16))
		return ;
	if ((*processes).argv[1][0] == REG_CODE && ((*processes).argv[1][1] < 1 || (*processes).argv[1][1] > 16))
		return ;
	if ((*processes).argv[1][0] != REG_CODE && (*processes).argv[1][0] != DIR_CODE)
		return ;
	if ((*processes).argv[0][0] == REG_CODE)
		one = (*processes).regs[(*processes).argv[0][1] - 1];
	else if ((*processes).argv[0][0] == DIR_CODE)
		one = (*processes).argv[0][1];
	else if ((*processes).argv[0][0] == IND_CODE)
	{
		i = ((*processes).argv[0][1] % IDX_MOD) + (*processes).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		one = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}
	if ((*processes).argv[1][0] == REG_CODE)
		two = (*processes).regs[(*processes).argv[1][1] - 1];
	else if ((*processes).argv[1][0] == DIR_CODE)
		two = (*processes).argv[1][1];
	else if ((*processes).argv[1][0] == IND_CODE)
	{
		i = ((*processes).argv[1][1] % IDX_MOD) + (*processes).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}

	i = (one + two) + (*processes).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	(*processes).regs[(*processes).argv[2][1] - 1] = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) +
	(map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	ft_printf("%s\n", "test_load lload_ind");
}

void long_fork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;

	i = 0;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	i = ((*processes).argv[0][1] % IDX_MOD) + (*processes).current_position;
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
	if ((*processes).argv[0][0] != REG_CODE || (*processes).argv[0][1] < 1 || (*processes).argv[0][1] > 16 ||
		(*processes).argv[1][0] || (*processes).argv[2][0])
		return ;
	ft_printf("%s\n", "aff -> test");
	ft_printf("%c\n", ((*processes).regs[(*processes).argv[0][1] - 1] % 256));
	map[0] = map[0];
}