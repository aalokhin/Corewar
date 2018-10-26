#include "corewar.h"

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

int find_arg_index(t_proc *processes, unsigned int target)
{
	int i;

	i = 0;
	while((*processes).argv[i][0] != target)
		i++;
	return (i);
}

void check_if_lives(t_proc *head_proc, t_cycle main_cycle)
{
	while (head_proc)
	{
		if ((*head_proc).last_live_cycle < main_cycle.cycles - main_cycle.cycle_die)
			(*head_proc).if_live = 0;
		head_proc = head_proc->next;
	}
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
	while (main_cycle.cycle_die > 0 && main_cycle.processes > 0)
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
			if ((*processes).child_proc_lives > 21)
			{
				(*processes).child_proc_lives = 0;
				main_cycle.cycle_die -= CYCLE_DELTA;
			}
			processes = processes->next;
			i++;
		}
		if (main_cycle.cycles != 0 && main_cycle.cycles % main_cycle.cycle_die)
		{
			check_if_lives(head_proc, main_cycle);
			main_cycle.checks_if_die++;
			if (main_cycle.checks_if_die == 10)
			{
				main_cycle.checks_if_die = 0;
				if (main_cycle.cycle_die == main_cycle.prev_cycle_die)
					main_cycle.cycle_die -= CYCLE_DELTA;
				main_cycle.prev_cycle_die = main_cycle.cycle_die;
			}
		}
		main_cycle.cycles++;
	}
}