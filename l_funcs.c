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
		if (tmp)
			(*tmp).child_proc_lives++;
	}
	if ((*child_proc).argv[0][0] &&
		(*child_proc).argv[0][1] >= 0 && (*child_proc).argv[0][1] < (*main_cycle).processes)
	{
		i = 0;
		other_proc = (*child_proc).argv[0][1];
		tmp = head_proc;
		while (i < (*main_cycle).processes && i != other_proc)
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
	t_proc *tmp;

	i = 0;
	arg_ind = 0;
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
	if ((*tmp).argv[1][0] != REG_CODE && (*tmp).argv[1][0] != DIR_CODE)
		return ;
	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = ((*tmp).argv[0][1] % IDX_MOD) + (*tmp).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		one = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = ((*tmp).argv[1][1] % IDX_MOD) + (*tmp).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}

	i = ((one + two) % IDX_MOD) + (*tmp).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) +
	(map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	ft_printf("%s\n", "test load_ind");
}

void store_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	unsigned int two;
	unsigned int three;
	t_proc *tmp;

	i = 0;
	two = 0;
	three = 0;
	tmp = processes;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16)
		return ;
	if ((*tmp).argv[2][0] != REG_CODE && (*tmp).argv[2][0] != DIR_CODE)
		return ;
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return ;
	if ((*tmp).argv[2][0] == REG_CODE && ((*tmp).argv[2][1] < 1 || (*tmp).argv[2][1] > 16))
		return ;
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = ((*tmp).argv[1][1]) % IDX_MOD;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}
	if ((*tmp).argv[2][0] == REG_CODE)
		three = (*tmp).regs[(*tmp).argv[2][1] - 1];
	else if ((*tmp).argv[2][0] == DIR_CODE)
		three = (*tmp).argv[2][1];

	i = (two + three + (*tmp).current_position) % IDX_MOD;
	ft_printf("%d %d \n", i, (*tmp).current_position);
	i %= MEM_SIZE;
	map[i] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x000000FF); 
	map[i + 1] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x0000FF00) >> 8; 
	map[i + 2] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x00FF0000) >> 16; 
	map[i + 3] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0xFF000000) >> 24;
	if ((*tmp).parent_nbr == -1)
	{
		(*main_cycle).indexes[i][0] = cur_proc + 1;
		(*main_cycle).indexes[i + 1][0] = cur_proc + 1;
		(*main_cycle).indexes[i + 2][0] = cur_proc + 1;
		(*main_cycle).indexes[i + 3][0] = cur_proc + 1;
	}
	else
	{
		(*main_cycle).indexes[i][0] = (*tmp).parent_nbr + 1;
		(*main_cycle).indexes[i + 1][0] = (*tmp).parent_nbr + 1;
		(*main_cycle).indexes[i + 2][0] = (*tmp).parent_nbr + 1;
		(*main_cycle).indexes[i + 3][0] = (*tmp).parent_nbr + 1;
	}
 	ft_printf("%s\n", "test_sti");
}

void ffork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	i = ((*tmp).argv[0][1] + (*tmp).current_position) % IDX_MOD;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	processes_add(tmp, map, main_cycle, i);
	//ft_printf("III%d %d\n", i, (*tmp).argv[0][1]);
	ft_printf("%s\n", "test_>fork");
}

void lload(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	ft_printf("%s\n", "test_load load");
}

void lload_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	int arg_ind;
	unsigned int one;
	unsigned int two;
	t_proc *tmp;

	i = 0;
	arg_ind = 0;
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
	if ((*tmp).argv[1][0] != REG_CODE && (*tmp).argv[1][0] != DIR_CODE)
		return ;
	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = ((*tmp).argv[0][1] % IDX_MOD) + (*tmp).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		one = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = ((*tmp).argv[1][1] % IDX_MOD) + (*tmp).current_position;
		if (i < 0 || i >= MEM_SIZE)
			i %= MEM_SIZE;
		two = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) + (map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	}

	i = (one + two) + (*tmp).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (map[i] << 24) + (map[(i + 1) % MEM_SIZE] << 16) +
	(map[(i + 2) % MEM_SIZE] << 8) + map[(i + 3) % MEM_SIZE];
	ft_printf("%s\n", "test_load lload_ind");
}

void long_fork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	i = ((*tmp).argv[0][1] % IDX_MOD) + (*tmp).current_position;
	if (i < 0 || i >= MEM_SIZE)
		i %= MEM_SIZE;
	processes_add(tmp, map, main_cycle, i);
	ft_printf("%s\n", "long->fork");
}

void aff(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	// надо узнать куда печатать символ и правильно прописать функцию
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16 ||
		(*tmp).argv[1][0] || (*tmp).argv[2][0])
		return ;
	ft_printf("%s\n", "aff -> test");
	ft_printf("%c\n", ((*tmp).regs[(*tmp).argv[0][1] - 1] % 256));
	map[0] = map[0];
}