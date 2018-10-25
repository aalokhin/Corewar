#include "corewar.h"
#include <stdio.h>


void live(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	int i;
	int other_proc;
	t_proc *tmp;

	i = 0;
	other_proc = 0;
	tmp = head_proc;
	while (i < (*main_cycle).processes && i != cur_proc)
	{
		tmp = tmp->next;
		i++;
	}
	(*tmp).if_live = 1;
	if ((*tmp).argv_vals[1][0] && (*tmp).argv_vals[1][1] < (*main_cycle).processes)
	{
		i = 0;
		other_proc = (*tmp).argv_vals[1][1];
		tmp = head_proc;
		while (i < (*main_cycle).processes && i != other_proc)
		{
			tmp = tmp->next;
			i++;
		}
		(*tmp).if_live = 1;
	}
}


void load_ind(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	ft_printf("%s\n", "test");
}

void store_ind(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	ft_printf("%s\n", "test");
}

void ffork(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	ft_printf("%s\n", "test");
}

void lload(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	ft_printf("%s\n", "test");
}

void lload_ind(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	ft_printf("%s\n", "test");
}

void long_fork(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	ft_printf("%s\n", "test");
}

void aff(t_proc *head_proc, int cur_proc, t_cycle *main_cycle)
{
	ft_printf("%s\n", "test");
}