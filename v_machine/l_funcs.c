#include "../corewar.h"

int live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	int other_proc;
	t_proc *tmp;
	t_proc *child_proc;
	
	i = 0;
	other_proc = 0;
	tmp = head_proc;
	child_proc = NULL;

	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	(*tmp).if_live = 1;
	(*tmp).last_live_cycle = (*main_cycle).cycles;
	(*tmp).lives++;
	child_proc = tmp;
	ft_printf("P%5d | live %d\n", (*tmp).id + 1, (*tmp).argv[0][1]);
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
	map[0] = map[0];
	return (1);
}


int load_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	if ((*tmp).argv[2][0] != REG_CODE || (*tmp).argv[2][1] < 1 || (*tmp).argv[2][1] > 16)
		return (0);
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] != REG_CODE && (*tmp).argv[1][0] != DIR_CODE)
		return (0);
	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = (*tmp).argv[0][1] % IDX_MOD + (*tmp).current_position;
		i = (i + MEM_SIZE) % MEM_SIZE;
		one = (map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
		(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).argv[1][1] % IDX_MOD + (*tmp).current_position;
		i = (i + MEM_SIZE) % MEM_SIZE;
		two = (map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
		(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	}

	i = (one + two) + (*tmp).current_position;
	ft_printf("P%5d | ldi %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
 	ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|', one, two, one + two, i);
	i = (i + MEM_SIZE) % MEM_SIZE;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
	(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	
 	(*main_cycle).cycles = (*main_cycle).cycles;
 	return (1);
}

int store_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	unsigned int two;
	unsigned int three;
	t_proc *tmp;

	i = 0;
	two = 0;
	three = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16)
		return (0);
	if ((*tmp).argv[2][0] != REG_CODE && (*tmp).argv[2][0] != DIR_CODE)
		return (0);
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return (0);
	if ((*tmp).argv[2][0] == REG_CODE && ((*tmp).argv[2][1] < 1 || (*tmp).argv[2][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[1][1] % IDX_MOD;
		i = (i + MEM_SIZE) % MEM_SIZE;
		two = (map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
		(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	}
	if ((*tmp).argv[2][0] == REG_CODE)
		three = (*tmp).regs[(*tmp).argv[2][1] - 1];
	else if ((*tmp).argv[2][0] == DIR_CODE)
		three = (*tmp).argv[2][1];

	i = (*tmp).current_position + (two + three);
	ft_printf("P%5d | sti r%d %d %d\n", cur_proc + 1, (*tmp).argv[0][1], two, three);
 	ft_printf("%8c -> store to %d + %d = %d (with pc and mod %d)\n", '|', two, three, two + three, i);
	i = (i + MEM_SIZE) % MEM_SIZE;
	//ft_printf("%d %d %d %d %d %d %d %d\n", i, (*tmp).current_position, (*main_cycle).cycles, (*tmp).argv[1][1], (*tmp).argv[2][1], (*tmp).regs[(*tmp).argv[0][1] - 1], two, three);
	
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

int ffork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;
	t_proc *head;

	i = 0;
	tmp = processes;
	head = processes;
	while (i < (*main_cycle).processes && (*tmp).id != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
	i = (i + MEM_SIZE) % MEM_SIZE;
	processes_add(&head, map, main_cycle, i, cur_proc);
	ft_printf("P%5d | fork %d (%d)\n", (*tmp).id + 1, (*tmp).argv[0][1], i);
	return (1);
}

int lload(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	}
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = (*tmp).current_position + (*tmp).argv[0][1];
		i = (i + MEM_SIZE) % MEM_SIZE;
		if (((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
			(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]) == 0)
			(*tmp).carry = 1;
		(*tmp).regs[(*tmp).argv[1][1] - 1] =
		(map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
		(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	}
	ft_printf("P%5d | lld %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1]);
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int lload_ind(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	if ((*tmp).argv[2][0] != REG_CODE || (*tmp).argv[2][1] < 1 || (*tmp).argv[2][1] > 16)
		return (0);
	if ((*tmp).argv[0][0] == REG_CODE && ((*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] == REG_CODE && ((*tmp).argv[1][1] < 1 || (*tmp).argv[1][1] > 16))
		return (0);
	if ((*tmp).argv[1][0] != REG_CODE && (*tmp).argv[1][0] != DIR_CODE)
		return (0);
	(*tmp).carry = 0;
	if ((*tmp).argv[0][0] == REG_CODE)
		one = (*tmp).regs[(*tmp).argv[0][1] - 1];
	else if ((*tmp).argv[0][0] == DIR_CODE)
		one = (*tmp).argv[0][1];
	else if ((*tmp).argv[0][0] == IND_CODE)
	{
		i = ((*tmp).argv[0][1] % IDX_MOD) + (*tmp).current_position;
		i = (i + MEM_SIZE) % MEM_SIZE;
		one = (map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
		(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	}
	if ((*tmp).argv[1][0] == REG_CODE)
		two = (*tmp).regs[(*tmp).argv[1][1] - 1];
	else if ((*tmp).argv[1][0] == DIR_CODE)
		two = (*tmp).argv[1][1];
	else if ((*tmp).argv[1][0] == IND_CODE)
	{
		i = ((*tmp).argv[1][1] % IDX_MOD) + (*tmp).current_position;
		i = (i + MEM_SIZE) % MEM_SIZE;
		two = (map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
		(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	}

	i = (one + two) + (*tmp).current_position;
	ft_printf("P%5d | lldi %d %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
 	ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|', one, two, one + two, i);
	i = (i + MEM_SIZE) % MEM_SIZE;
	if (((map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
	(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE]) == 0)
			(*tmp).carry = 1;
	(*tmp).regs[(*tmp).argv[2][1] - 1] = (map[i] << 24) + (map[(i + MEM_SIZE + 1) % MEM_SIZE] << 16) +
	(map[(i + MEM_SIZE + 2) % MEM_SIZE] << 8) + map[(i + MEM_SIZE + 3) % MEM_SIZE];
	(*main_cycle).cycles = (*main_cycle).cycles;
	return (1);
}

int long_fork(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;
	t_proc *head;

	i = 0;
	tmp = processes;
	head = processes;
	while (i < (*main_cycle).processes && (*tmp).id != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	i = ((*tmp).argv[0][1] % IDX_MOD) + (*tmp).current_position;
	i = (i + MEM_SIZE) % MEM_SIZE;
	processes_add(&head, map, main_cycle, i, cur_proc);
	ft_printf("P%5d | lfork %d (%d)\n", (*tmp).id + 1, (*tmp).argv[0][1], i);
	return (1);
}

int aff(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	// надо узнать куда печатать символ и правильно прописать функцию
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16 ||
		(*tmp).argv[1][0] || (*tmp).argv[2][0])
		return (0);
	ft_printf("%d %s\n", cur_proc + 1, "aff -> test");
	ft_printf("%c\n", ((*tmp).regs[(*tmp).argv[0][1] - 1] % 256));
	(*main_cycle).cycles = (*main_cycle).cycles;
	map[0] = map[0];
	return (1);
}