#include "corewar.h"

void live(t_proc *head_proc, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;
	unsigned int other_proc;
	t_proc *tmp;
	int arg_ind;

	i = 0;
	other_proc = 0;
	arg_ind = 0;
	tmp = head_proc;
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
	if ((*tmp).argv[arg_ind][0] &&
		(*tmp).argv[arg_ind][1] < (*main_cycle).processes)
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
			{
				(*tmp).child_proc_lives++;
			}
			
		}
	}
	ft_printf("%s\n", "test live");
	map[0] = map[0];
}


void load_ind(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	if ((*processes).argv[0][1] == IND_CODE)
	{
		i = ((*processes).argv[2][1] % IDX_MOD) + (*processes).current_position;
		(*processes).argv[0][1] = (map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];
	}

	i = (((*processes).argv[0][1] + (*processes).argv[1][1]) % IDX_MOD) + (*processes).current_position;

	(*processes).argv[2][1] = (map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];
	

	ft_printf("%s\n", "test load_ind");

	map[0] = map[0];
}

void store_ind(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	if ((*processes).argv[1][1] == IND_CODE)
	{
		i = (*processes).argv[1][1] % IDX_MOD;
		(*processes).argv[1][1] = (map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];
	}

	i = ( ((*processes).argv[1][1] + (*processes).argv[2][1] ) % IDX_MOD) + (*processes).current_position;
	

	map[i] = (*processes).argv[0][1];
	(*main_cycle).indexes[i][0] = cur_proc;
 	ft_printf("%s\n", "test_sti");

 	map[0] = map[0];
}

void ffork(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	//ft_printf("(*processes).argv[arg_ind][1]%d\n", (*processes).argv[arg_ind][1]);
	i = ((*processes).argv[arg_ind][1] % IDX_MOD) + (*processes).current_position;
	processes_add(processes, map, main_cycle, i, (*processes).id);

	ft_printf("%s\n", "test_>fork");

	map[0] = map[0];
}

void lload(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if ((*processes).argv[0][0] == DIR_CODE) //t_reg -> index of n array
	{
		(*processes).regs[(*processes).argv[0][1]] = (*processes).argv[0][1];
	}
	else if ((*processes).argv[0][0] == IND_CODE)
	{

		(*processes).argv[0][1] = (*processes).argv[0][1];
		i = (*processes).current_position + (*processes).argv[0][1];
		

		(*processes).regs[(*processes).argv[0][1]] =
		(map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];

	}
	if ((*processes).regs[(*processes).argv[0][1]] == 0)
		(*processes).carry = 1;
	else
		(*processes).carry = 0;
	ft_printf("%s\n", "test_load load");
	map[0] = map[0];

}

void lload_ind(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{

	//надо разобраться 

	//**********************************************************!!!!!! FAAAAAAAAKE

	unsigned int i;


	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	if ((*processes).argv[0][0] == DIR_CODE) //t_reg -> index of n array
	{
		(*processes).regs[(*processes).argv[0][1]] = (*processes).argv[0][1];
	}
	else if ((*processes).argv[0][0] == IND_CODE)
	{

		(*processes).argv[0][1] = (*processes).argv[0][1];
		i = (*processes).current_position + (*processes).argv[0][1];
		

		(*processes).regs[(*processes).argv[0][1]] =
		(map[i + 3] << 24) + (map[i + 2] << 16) + (map[i + 1] << 8) + map[i];

	}
	if ((*processes).regs[(*processes).argv[0][1]] == 0)
		(*processes).carry = 1;
	else
		(*processes).carry = 0;


	map[0] = map[0];

	//***********************************************************************!!!!!! FAAAAAAAAKE

	ft_printf("%s\n", "test_load lload_ind");
}

void long_fork(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
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
	//ft_printf("(*processes).argv[arg_ind][1]%d\n", (*processes).argv[arg_ind][1]);//
	i = (*processes).argv[arg_ind][1] + (*processes).current_position;
	//ft_printf("i%d\n", i);
	processes_add(processes, map, main_cycle, i, (*processes).id);

	ft_printf("%s\n", "long->fork");

	map[0] = map[0];

}

void aff(t_proc *processes, unsigned int cur_proc, t_cycle *main_cycle, unsigned char *map)
{
	unsigned int i;

	i = 0;

	while (i < (*main_cycle).processes && i != cur_proc)
	{
		processes = processes->next;
		i++;
	}
	ft_printf("%s\n", "aff -> test");
	//ft_printf("%c\n", ((*processes).regs[(*processes).argv[0][1]] % 256));
	map[0] = map[0];
}