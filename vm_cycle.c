#include "corewar.h"

void processes_add(t_proc *processes, unsigned char *map, t_cycle *main_cycle, int index, int cur_proc)
{
	t_proc *tmp;
	t_proc *parent;

	tmp = NULL;

	(*main_cycle).processes++;
	while (processes)
	{
		if ((*processes).id == cur_proc)
			parent = processes;
		processes = processes->next;
	}
	tmp = (t_proc *)malloc(sizeof(t_proc));
	tmp->id = (*main_cycle).processes - 1;
	tmp->current_position = index;
	tmp->carry = 0;
	tmp->parent_nbr = cur_proc;
	tmp->if_live = 1;
	ft_printf("ind%d\n", tmp->current_position);
	tmp->cmd = map[tmp->current_position];
	ft_printf("ind%d\n", tmp->current_position);
	(*main_cycle).indexes[tmp->current_position][0] = tmp->id;
	ft_printf("ind%d\n", tmp->current_position);
	(*main_cycle).indexes[tmp->current_position][1] = 1;
	tmp->cycles_wait = op_tab[map[tmp->current_position] - 1].cycles_wait;
	tmp->last_live_cycle = 0;
	tmp->child_proc_lives = 0;
	tmp->next = NULL;
	processes = tmp;

}

int find_arg_index(t_proc *processes, int target)
{
	int i;

	i = 0;
	while(i < 3 && (*processes).argv[i][0] != target)
		i++;
	return (i);
}

void check_if_lives(t_proc *head_proc, t_cycle *main_cycle)
{
	int winner;

	winner = 0;
	while (head_proc)
	{
		if ((*head_proc).last_live_cycle < (*main_cycle).cycles - (*main_cycle).cycle_die)
			(*head_proc).if_live = 0;
		if ((*head_proc).last_live_cycle > winner)
			(*head_proc).last_live_cycle = winner;
		head_proc = head_proc->next;
	}
	(*main_cycle).current_winner = winner;
}

void fill_start_map_id(t_cycle *main_cycle, header_t bots[4], t_flags *params)
{
	unsigned int i;
	unsigned int j;
	unsigned int lim;

	i = 0;
	j = 0;
	lim = 0;
	while (j < (*params).bots_quantity)
	{
		i = bots[j].start_index;
		lim = bots[j].prog_size + i;
		while (i < lim)
		{
			(*main_cycle).indexes[i][0] = j + 1;
			i++;
		}
		j++;
	}	
}


		

void vm_cycle(unsigned char *map, t_flags *params, header_t bots[4])
{
	int i;
	t_cycle main_cycle;
	t_proc *processes;
	t_proc *head_proc;
	int id_counter;
	
	i = 0;
	processes = NULL;
	id_counter = 0;
	main_cycle_init(&main_cycle, params);
	fill_start_map_id(&main_cycle, bots, params);
	processes = processes_init(params, bots, map, main_cycle.indexes);
	head_proc = processes;
	while (main_cycle.cycle_die > 0 && main_cycle.processes > 0)
	{
		//ft_printf("something weird\n");
		i = 0;
		processes = head_proc;
		if ((*params).ncurses == 1)
			map_to_screen(map, &main_cycle, params, head_proc);
		while (i < main_cycle.processes && processes)
		{
			//ft_printf("Segfault in i == %d \n",  i);
			if ((*processes).current_position >= 0 && (*processes).current_position < MEM_SIZE)
			{
				if (op_tab[map[(*processes).current_position] - 1].codage)
				{
					id_counter = (*processes).current_position + 1;
					take_args(map[id_counter], processes);
					get_args_values(processes, map, &id_counter);
				}
				else
				{
					id_counter = (*processes).current_position;
					(*processes).argv[0][0] = DIR_CODE;
					get_arg_vals[(*processes).argv[0][0]](processes, map, 0, &id_counter);
				}
				if ((*processes).if_live && map[(*processes).current_position] >= 1
				&& map[(*processes).current_position] <= 16)
				{
					instruct[map[(*processes).current_position] - 1](head_proc, i, &main_cycle, map);
					if (map[(*processes).current_position] != 9)
						(*processes).current_position = id_counter + 1;
					clear_argv_arr(processes);
				}
				else
					(*processes).current_position++;
			}
			else
				(*processes).current_position = (*processes).current_position + ((*processes).argv[find_arg_index(processes, IND_CODE)][1]% IDX_MOD);
			
			main_cycle.indexes[(*processes).current_position][0] = i;
			main_cycle.indexes[(*processes).current_position][1] = 1;
			if ((*processes).child_proc_lives > 21)
			{
				(*processes).child_proc_lives = 0;
				main_cycle.cycle_die -= CYCLE_DELTA;
			}
			processes = processes->next;
			i++;
		}

		if (main_cycle.cycles != 0 && main_cycle.cycles % main_cycle.cycle_die == 0)
		{
			//ft_printf("we are in the if number 3) \n");

			check_if_lives(head_proc, &main_cycle);
			main_cycle.checks_if_die++;
			if (main_cycle.checks_if_die == 10)
			{
				main_cycle.checks_if_die = 0;
				if (main_cycle.cycle_die == main_cycle.prev_cycle_die)
					main_cycle.cycle_die -= CYCLE_DELTA;
				main_cycle.prev_cycle_die = main_cycle.cycle_die;
			}
		}
		
		//ft_printf("we are in  main cycle %d \n", main_cycle.cycles);
		main_cycle.cycles++;
	}
	ft_printf("we exited main cycle\n");

}