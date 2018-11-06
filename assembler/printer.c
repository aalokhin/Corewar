
#include "asm.h"


	// printf("%s\n", "command name");
	// printf("%s\n", "codage");
	// distance_to_label();


// 0b68 0100 0f00 01
// 06 6401 0000 0000 01
// 01 0000 0001 
// 09ff fb

// int 	find_needed_label(t_binfile *file, char *needed_label)
// {

// }

// int		distance_to_label(t_binfile *file, t_lable *label, char *str)
// {
// 	int		distance = 0;
// 	char 	**copy;

// 	copy = ft_strsplit(str, '%');
// 	printf(" === %s\n",copy[0]);
// 	printf("%s %s\n", label->label_name, file->arg_name);
// 	//find_needed_label(file, t_lable *label );
// 	return (distance);
// }

void	command_printer(t_lable *label)
{
	t_t *tmp;

	tmp = label->instruct;
	while (tmp)
	{
		ft_printf("%x ", tmp->c_name + 1);
		if (tmp->has_codage)
			ft_printf("%x ", tmp->codage);
		if (tmp->a[0] && ft_strchr(tmp->a[0], '%') && ft_strchr(tmp->a[0], ':'))
		{
			//distance_to_label(file, label, tmp->a[0]);
			ft_printf("we have label here");
		}
		if (tmp->a[1] && ft_strchr(tmp->a[1], '%') && ft_strchr(tmp->a[1], ':'))
		{
			//distance_to_label(file, label, tmp->a[1]);
			ft_printf("we have label here");
		}
		if (tmp->a[2] && ft_strchr(tmp->a[2], '%') && ft_strchr(tmp->a[2], ':'))
		{
			//distance_to_label(file, label, tmp->a[2]);
			ft_printf("we have label here");
		}

		//printf("COMMAND == %s \n", g_op_tab[tmp->c_name].name);
		// printf("Arguments = %d %d %d %d\n", tmp->arg[0], tmp->arg[1], tmp->arg[2], 00);
		// printf("Arguments =  %s %s %s\n", tmp->a[0], tmp->a[1], tmp->a[2]);
		printf("\n");
		tmp = tmp->next;
	}
}

void	labels_printer(t_binfile *file)
{
	t_lable		*tmp;

	tmp = file->labels_list;
	while (tmp)
	{
		//printf("LABEL ==== %s \n", tmp->label_name);
		command_printer(tmp);
		tmp = tmp->next;
	}
}

void	main_printer(t_binfile *file)
{
	labels_printer(file);
}
