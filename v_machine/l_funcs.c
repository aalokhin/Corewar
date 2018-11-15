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
	(*tmp).live_cycle = 0;
	child_proc = tmp;
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | live %d\n", (*tmp).id + 1, (*tmp).argv[0][1]);
	if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] <= 0)
	{
		if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] < 0)
		(*child_proc).argv[0][1] = ((*child_proc).argv[0][1] * -1) - 1;
		else if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] > 0)
			(*child_proc).argv[0][1] -= 1;
		if ((*child_proc).argv[0][0] &&
			((*child_proc).argv[0][1] >= 0 && (*child_proc).argv[0][1] <= (*head_proc).id))
		{
			i = 0;
			other_proc = (*child_proc).argv[0][1];
			tmp = head_proc;
			while (tmp && (*tmp).id != other_proc)
				tmp = tmp->next;
			if (tmp && (*tmp).if_live && (*tmp).last_live_cycle > 0)
			{
				(*tmp).if_live = 1;
				(*tmp).last_live_cycle = (*main_cycle).cycles;
				//(*tmp).lives++;
				if (((*main_cycle).verbose & 1))
					//ft_printf("A process shows that player %s (champion_name) is alive.\n", (*tmp).name);
				{
					//if ((*tmp).parent_nbr == -1)
						ft_printf("Player %d (%s) is said to be alive\n", (*child_proc).argv[0][1] + 1, (*tmp).name);
					//else
						//ft_printf("Player %d (%s) is said to be alive\n", (*tmp).parent_nbr + 1, (*tmp).name);
				}
					
			}
		}
	}
	map[0] = map[0];
	return (1);
}

/*
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
	(*tmp).live_cycle = 0;
	child_proc = tmp;
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | live %d\n", (*tmp).id + 1, (*tmp).argv[0][1]);
	if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] < 0)
		(*child_proc).argv[0][1] = ((*child_proc).argv[0][1] * -1) - 1;
	else if ((*child_proc).argv[0][0] && (*child_proc).argv[0][1] > 0)
		(*child_proc).argv[0][1] -= 1;
	if ((*child_proc).argv[0][0] &&
		((*child_proc).argv[0][1] >= 0 && (*child_proc).argv[0][1] <= (*head_proc).id))
	{
		i = 0;
		other_proc = (*child_proc).argv[0][1];
		tmp = head_proc;
		while (tmp && (*tmp).id != other_proc)
			tmp = tmp->next;
		if (tmp)
		{
			(*tmp).if_live = 1;
			(*tmp).last_live_cycle = (*main_cycle).cycles;
			(*tmp).lives++;
			if (((*main_cycle).verbose & 1))
				//ft_printf("A process shows that player %s (champion_name) is alive.\n", (*tmp).name);
				ft_printf("Player %d (%s) is said to be alive\n", (*child_proc).argv[0][1] + 1, (*tmp).name);
		}
	}
	map[0] = map[0];
	return (1);
}
*/

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
	if (((*main_cycle).verbose >> 2) & 1)
	{
		ft_printf("P%5d | ldi %d %d r%d\n", cur_proc + 1, one, two, (*tmp).argv[2][1]);
 		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|', one, two, one + two, i);
	}
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
	if (((*main_cycle).verbose >> 2) & 1)
	{
		ft_printf("P%5d | sti r%d %d %d\n", cur_proc + 1, (*tmp).argv[0][1], two, three);
 		ft_printf("%8c -> store to %d + %d = %d (with pc and mod %d)\n", '|', two, three, two + three, i);
	}
	i = (i + MEM_SIZE) % MEM_SIZE;
	map[(i + MEM_SIZE + 3) % MEM_SIZE] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x000000FF); 
	map[(i + MEM_SIZE + 2) % MEM_SIZE] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x0000FF00) >> 8; 
	map[(i + MEM_SIZE + 1) % MEM_SIZE] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0x00FF0000) >> 16; 
	map[i] = ((*tmp).regs[(*tmp).argv[0][1] - 1] & 0xFF000000) >> 24;
	if ((*tmp).parent_nbr == -1)
	{
		(*main_cycle).indexes[i][0] = (*tmp).real_id + 1;
		(*main_cycle).indexes[(i + MEM_SIZE + 1) % MEM_SIZE][0] = (*tmp).real_id + 1;
		(*main_cycle).indexes[(i + MEM_SIZE + 2) % MEM_SIZE][0] = (*tmp).real_id + 1;
		(*main_cycle).indexes[(i + MEM_SIZE + 3) % MEM_SIZE][0] = (*tmp).real_id + 1;
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
	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	i = (*tmp).current_position + (*tmp).argv[0][1] % IDX_MOD;
	i = (i + MEM_SIZE) % MEM_SIZE;
	processes_add(&head, map, main_cycle, i, cur_proc);
	if (((*main_cycle).verbose >> 2) & 1)
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
	if ((*tmp).argv[0][0] == DIR_CODE)
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
	if (((*main_cycle).verbose >> 2) & 1)
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
	if (((*main_cycle).verbose >> 2) & 1)
	{
		ft_printf("P%5d | lldi %d %d r%d\n", cur_proc + 1, (*tmp).argv[0][1], (*tmp).argv[1][1], (*tmp).argv[2][1]);
 		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|', one, two, one + two, i);
	}
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
	while (tmp && (*tmp).id != cur_proc)
		tmp = tmp->next;
	i = (*tmp).argv[0][1] + (*tmp).current_position;
	if (((*main_cycle).verbose >> 2) & 1)
		ft_printf("P%5d | lfork %d (%d)\n", (*tmp).id + 1, (*tmp).argv[0][1], i);
	i = (i + MEM_SIZE) % MEM_SIZE;
	processes_add(&head, map, main_cycle, i, cur_proc);
	
	return (1);
}

int aff(t_proc *processes, int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	int i;
	t_proc *tmp;

	i = 0;
	tmp = processes;
	if ((*tmp).argv[0][0] != REG_CODE || (*tmp).argv[0][1] < 1 || (*tmp).argv[0][1] > 16 ||
		(*tmp).argv[1][0] || (*tmp).argv[2][0])
		return (0);
	ft_printf("%s", "Aff: ");
	ft_printf("%c\n", ((*tmp).regs[(*tmp).argv[0][1] - 1] % 256));
	(*main_cycle).cycles = (*main_cycle).cycles;
	cur_proc = map[0];
	return (1);
}