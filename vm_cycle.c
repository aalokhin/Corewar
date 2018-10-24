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

void take_args(unsigned char codage, int argv[3][2])
{
	 if((codage & 192) == 64)
        argv[0][0] = 1;
    else if((codage & 192) == 192)
        argv[0][0] = 3;
    else if((codage & 192) == 128 )
        argv[0][0] = 2;
    else
        argv[0][0] = 0;
    if((codage & 48 ) == 32)
        argv[1][0] = 2;
    else if((codage & 48 ) == 48 )
        argv[1][0] = 3;
    else if((codage & 48 ) == 16)
        argv[1][0] = 1;
    else
        argv[1][0] = 0;
    if((codage & 12) == 8 )
        argv[2][0] = 2;
    else if((codage & 12) == 12)
        argv[2][0] = 3;
    else if((codage & 12) == 4)
        argv[2][0] = 1;
    else
        argv[2][0] = 0;
}

void vm_cycle(unsigned char *map, t_flags *params, header_t bots[4])
{
	int i;
	t_cycle main_cycle;
	t_proc *processes;
	t_proc *head_proc;

	i = 0;
	processes = NULL;
	main_cycle_init(&main_cycle, params);
	processes_init(processes, params, bots, map);
	head_proc = processes;
	//ft_printf("%d\n", map[1] & 48);
	//instruct[0]();
	while (CYCLE_TO_DIE > 0 && main_cycle.processes > 0)
	{
		i = 0;
		processes = head_proc;
		while (i < main_cycle.processes)
		{
			if ((*processes).if_live && map[(*processes).current_position] >= 1
				&& map[(*processes).current_position] <= 16)
			{
				if (op_tab[map[(*processes).current_position]].codage)
					take_args(map[(*processes).current_position + 1], (*processes).argv);
				/*else
				{
					(*processes).argv[0][0] = 2;
					(*processes).argv[0][1] = 2;
				}*/

				instruct[map[(*processes).current_position]]();
			}
			(*processes).argv[0][0] = 0;
			(*processes).argv[0][1] = 0;
			(*processes).argv[1][0] = 0;
			(*processes).argv[1][1] = 0;
			(*processes).argv[2][0] = 0;
			(*processes).argv[2][1] = 0;
			processes = processes->next;
			i++;
		}
	}
}