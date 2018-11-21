#include "asm.h"

void				ft_clean_parse(char **parse)
{
	int i;

	i = 0;
	while (parse[i])
		ft_strdel(&parse[i++]);
	free(parse);
}


void 		print_check(t_binfile	*bin)
{
	t_lable 	*tmp;
	t_t 		*tmp2;

	tmp = bin->labels_list;
	while(tmp)
	{
		printf("lable name is [%s]\n", tmp->label_name);
		tmp2 = tmp->instruct;
		while(tmp2)
		{
			printf("	instruct name [%s]\n", tmp2->name_c);
			tmp2 = tmp2->next;  
		}
		tmp = tmp->next;
	}
	printf("all printed\n");
}

void		clean_instructs(t_lable *element)
{
	t_t		*instruct;
	t_t 	*tmp;

	instruct = element->instruct;
	while(instruct)
	{
		tmp = instruct;
		if (tmp->name_c)
			ft_strdel(&(tmp->name_c));
		instruct = instruct->next;
		free(tmp);
	}
	free(element);
}

void			clean_labels(t_lable **head)
{
	t_lable		*next;

	next = *head;
	if (!head)
		return ;
	while(*head != NULL)
	{
		next = (*head)->next;
		if ((*head)->label_name)
			ft_strdel(&(*head)->label_name);
		clean_instructs(*head);
		(*head) = next;
	}
}

void		ft_clean_all(t_binfile	*bin)
{

	ft_strdel(&((*bin).f_contents));
	ft_strdel(&((*bin).copy)); 
	ft_strdel(&((*bin).arg_name)); 
	ft_strdel(&((*bin).res_arg_name)); 
	ft_strdel(&((*bin).name)); 
	ft_strdel(&((*bin).comment));
	if ((*bin).labels_list)
		clean_labels(&((*bin).labels_list));

}