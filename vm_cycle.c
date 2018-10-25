#include "corewar.h"
#include <stdio.h>

void main_cycle_init(t_cycle *main_cycle, t_flags *params)
{
	(*main_cycle).cycles = 0;
	(*main_cycle).processes = (*params).bots_quantity;
	(*main_cycle).second_limit = 0;
	(*main_cycle).cycle_die = CYCLE_TO_DIE;
	(*main_cycle).cycle_delta = CYCLE_DELTA;
	(*main_cycle).nbr_live = NBR_LIVE;
	(*main_cycle).max_checks = MAX_CHECKS;
	(*main_cycle).current_winner = -1;
}

void processes_add(t_proc *processes, unsigned char *map, t_cycle *main_cycle, int index, int cur_proc)
{
	t_proc *tmp;

	tmp = NULL;
	(*main_cycle).processes++;
	while (processes)
	{
		processes = processes->next;
	}
	tmp = (t_proc *)malloc(sizeof(t_proc));
	tmp->id = (*main_cycle).processes - 1;
	tmp->current_position = index;
	tmp->carry = -1;
	tmp->parent_nbr = cur_proc;
	tmp->if_live = 1;
	tmp->cmd = map[(*processes).current_position];
	tmp->cycles_wait = op_tab[tmp->cmd - 1].cycles_wait;
	tmp->next = NULL;
	processes = tmp;
}

void processes_init(t_proc *processes, t_flags *params, header_t bots[4], unsigned char *map)
{
	unsigned int i;
	
	i = 0;
	while (i < (*params).bots_quantity)
	{
		processes = (t_proc *)malloc(sizeof(t_proc));
		(*processes).id = i;
		(*processes).current_position = bots[i].start_index;
		(*processes).carry = -1;
		(*processes).parent_nbr = -1;
		(*processes).if_live = 1;
		(*processes).cmd = map[(*processes).current_position];
		(*processes).cycles_wait = op_tab[(*processes).cmd - 1].cycles_wait;
		(*processes).next = NULL;
		processes = (*processes).next;
		i++;
	}
}

void get_t_dir_value(t_proc *processes, unsigned char *map, 
	int arg_ind, int *id_counter)
{
	int size;
	short tmp_2;
	unsigned int tmp_4;

	size = 0;
	tmp_2 = 0;
	tmp_4 = 0;
	if (!op_tab[map[(*processes).current_position]].label)
	{
		size = 4;
		tmp_2 = (unsigned int)((map[(*id_counter) + 4] << 24) + (map[(*id_counter) + 3] << 16) + (map[(*id_counter) + 2] << 8) + map[(*id_counter) + 1]);
		(*processes).argv[arg_ind][1] = tmp_2;
	}
	else
	{
		size = 2;
		tmp_2 = (short)((map[(*id_counter) + 2] << 8) + map[(*id_counter) + 1]);
		(*processes).argv[arg_ind][1] = tmp_2;
	}
	(*id_counter) += size;
	//(*processes).argv_vals[1][0] = 1;
	//(*processes).argv_vals[1][1] = (*processes).argv[arg_ind][1];
}

void get_t_ind_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter)
{
	short tmp;
	short res;

	tmp = 0;
	res = 0;
	tmp = (short)((map[(*id_counter) + 2] << 8) + map[(*id_counter) + 1]);
	(*processes).argv[arg_ind][1] = tmp;
	(*id_counter) += 2;
	res = ((map[(*processes).argv[arg_ind][1] + 3] << 24) + (map[(*processes).argv[arg_ind][1] + 2] << 16) +
		(map[(*processes).argv[arg_ind][1] + 1] << 8) + map[(*processes).argv[arg_ind][1]]);
	//(*processes).argv_vals[2][0] = 1;
	//(*processes).argv_vals[2][1] = res;
}

void get_t_reg_value(t_proc *processes, unsigned char *map, int arg_ind, int *id_counter)
{
	(*processes).argv[arg_ind][1] = (unsigned char)map[(*id_counter) + 1];
	//(*processes).argv_vals[0][0] = 1;
	//(*processes).argv_vals[0][1] = (*processes).argv[arg_ind][1];
	(*id_counter)++;
}

int find_arg_index(t_proc *processes, unsigned int target)
{
	int i;

	i = 0;
	while((*processes).argv[i][0] != target)
		i++;
	return (i);
}

void get_args_values(t_proc *processes, unsigned char *map, int *id_counter)
{
	if ((*processes).argv[0][0])
		get_arg_vals[(*processes).argv[0][0] - 1](processes, map, 0, id_counter);
	if ((*processes).argv[1][0])
		get_arg_vals[(*processes).argv[1][0] - 1](processes, map, 1, id_counter);
	if ((*processes).argv[2][0])
		get_arg_vals[(*processes).argv[2][0] - 1](processes, map, 2, id_counter);

}

void take_args(unsigned char codage, unsigned int argv[3][2])
{
	if((codage & 192) == 64)
        argv[0][0] = REG_CODE;
    else if((codage & 192) == 192)
        argv[0][0] = IND_CODE;
    else if((codage & 192) == 128 )
        argv[0][0] = DIR_CODE;
    if((codage & 48 ) == 32)
        argv[1][0] = DIR_CODE;
    else if((codage & 48 ) == 48 )
        argv[1][0] = IND_CODE;
    else if((codage & 48 ) == 16)
        argv[1][0] = REG_CODE;
    if((codage & 12) == 8 )
        argv[2][0] = DIR_CODE;
    else if((codage & 12) == 12)
        argv[2][0] = IND_CODE;
    else if((codage & 12) == 4)
        argv[2][0] = REG_CODE;
}

void clear_argv_arr(t_proc *processes)
{
	(*processes).argv[0][0] = 0;
	(*processes).argv[0][1] = 0;
	(*processes).argv[1][0] = 0;
	(*processes).argv[1][1] = 0;
	(*processes).argv[2][0] = 0;
	(*processes).argv[2][1] = 0;

	/*(*processes).argv_vals[0][0] = 0;
	(*processes).argv_vals[0][1] = 0;
	(*processes).argv_vals[1][0] = 0;
	(*processes).argv_vals[1][1] = 0;
	(*processes).argv_vals[2][0] = 0;
	(*processes).argv_vals[2][1] = 0;*/
}

void vm_cycle(unsigned char *map, t_flags *params, header_t bots[4])
{
	unsigned int i;
	t_cycle main_cycle;
	t_proc *processes;
	t_proc *head_proc;
	int id_counter;

	i = 0;
	processes = NULL;
	id_counter = 0;
	main_cycle_init(&main_cycle, params);
	processes_init(processes, params, bots, map);
	head_proc = processes;
	//ft_printf("%d\n", map[1] & 48);
	while (CYCLE_TO_DIE > 0 && main_cycle.processes > 0)
	{
		i = 0;
		processes = head_proc;
		while (i < main_cycle.processes)
		{
			if ((*processes).if_live && map[(*processes).current_position] >= 1
				&& map[(*processes).current_position] <= 16)
			{
				if (op_tab[map[(*processes).current_position] - 1].codage)
				{
					id_counter = (*processes).current_position + 1;
					take_args(map[id_counter], (*processes).argv);
					get_args_values(processes, map, &id_counter);
				}
				else
				{
					id_counter = (*processes).current_position;
					(*processes).argv[0][0] = DIR_CODE;
					get_arg_vals[(*processes).argv[0][0]](processes, map, 0, &id_counter);
				}
				instruct[map[(*processes).current_position] - 1](head_proc, i, &main_cycle, map);
				(*processes).current_position = id_counter + 1;
				clear_argv_arr(processes);
			}
			else
				(*processes).current_position++;
			processes = processes->next;
			i++;
		}
	}
}