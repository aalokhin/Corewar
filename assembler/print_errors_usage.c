#include "asm.h"


// #ifndef MUSIC_H
// # define MUSIC_H

// /*
// ** Music structure
// */

// # define M                              v->music
// # define MSTART                 1
// # define MDIE                   2
// # define MEND                   4

// typedef struct                  s_single_music_info
// {
//         unsigned char           start_duration;
//         unsigned char           die_duration;
//         char                            *play_start;
//         char                            *play_die;
//         char                            *play_end;

// }                                               t_smi;

// struct                                  s_music
// {
//         unsigned char           music;
//         unsigned char           to_wait;
//         t_smi                           *cmi;

//         time_t                          playing;
// };

// #endif


// #define TMP                     t->play_start

// static const t_smi      g_all_music_info[] = {
//         {0, 0, NULL, NULL, NULL},
//         {14, 14, "venom/", NULL, NULL},
//         {8, 4, "skibidi/", NULL, NULL},
//         {18, 12, "bigshaq/", NULL, NULL},
//         {0, 0, NULL, NULL, NULL}
// };

// static bool                     init(t_vm *v)
// {
//         t_smi                   *const t = (t_smi *const)(g_all_music_info + M.music);

//         TMP = ft_strjoin(
//         "afplay /Users/vbrazas/projects/archive/corewar/vm/music/"
//         , TMP);
//         t->play_die = ft_strjoin(TMP, "die.mp3 &> /dev/null &");
//         t->play_end = ft_strjoin(TMP, "end.mp3 &> /dev/null &");
//         t->play_start = ft_strjoin(TMP, "start.mp3 &> /dev/null &");
//         M.cmi = (t_smi*)t;
//         return (true);
// }

// void                            play_music(t_vm *v, int flag)
// {
//         static int              is_allocate = 0;


//         if (!A.is_ncurses || !M.music)
//                 return ;
//         if (is_allocate == 0)
//                 init(v) && ++is_allocate;
//         if (flag == MSTART)
//         {
//                 system(M.cmi->play_start);
//                 M.to_wait = M.cmi->start_duration;
//                 M.playing = time(NULL);
//         }
//         else if (flag == MDIE
//         && M.playing + M.to_wait < time(NULL))
//         {
//                 system(M.cmi->play_die);
//                 M.to_wait = M.cmi->die_duration;
//                 M.playing = time(NULL);
//         }
//         else if (flag == MEND)
//         {
//                 system("pkill afplay");
//                 system(M.cmi->play_end);
//         }
// }


void 			ft_print_success(t_binfile *bin)
{
	int 		len;

	
	len = ft_strlen(bin->arg_name);
	printf("Writing output program to %s\n", bin->res_arg_name);
	system("afplay /Users/aalokhin/Downloads/Sound_15025.mp3");



}

void			ft_print_usage()
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("%117s\n", "-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output");
	ft_printf("%117s\n", "-d : Compiles all files in the given directory");
	ft_printf("%117s\n", "-D : Compiles all files in the given directory and its subdirectories");
}

void 			ft_print_inv_f(char *s_file)
{
	ft_printf("Source file error ====>[%s]<=== \n", s_file);

	// should be something like  ft_printf("Syntax error at token [TOKEN][001:001] END \"(null)\"");
}




void	ft_print_inv_input()
{
	ft_printf("Input error\n");
}

int			error_message_label(t_binfile *file, t_t *token, char *label, char *arg)
{
	int 	colomn = define_line_colomn(file->copy, arg, token->line_num);

	ft_printf("No such label %s while attempting to dereference token [TOKEN][%d:%d] %s \"%s\"\n", label, token->line_num + 1, colomn + 1, "DIRECT_LABEL", arg);
	return (0);
}

int 		error_command(t_binfile *file, char *str, int line_num)
{
	int 	colomn = define_line_colomn(file->copy, str, line_num);

	ft_printf("Invalid instruction at token [TOKEN][%d:%d] INSTRUCTION \"%s\"\n", line_num + 1, colomn, str);
	return (0);
}


int			error_message(t_binfile *file, char *arg, int line_num)
{
	char 	*e;
	int 	colomn;

	colomn = define_line_colomn(file->copy, arg, line_num);
	//printf("%s %d\n", arg, colomn);
	if (ft_strstr(arg, ".name") || ft_strstr(arg, ".comment"))
	{
		ft_printf("Syntax error at token [TOKEN][%d:%d] ENDLINE\n", line_num + 1, colomn);
		return (0);
	}
	if (ft_strchr(arg ,'r') && !(ft_strchr(arg ,'%')))
		e = ft_strdup("REGISTER");
	else if (ft_strstr(arg, "%:"))
		e = ft_strdup("DIRECT_LABEL");
	else if (ft_strchr(arg ,'%'))
		e = ft_strdup("DIRECT");
	else if (ft_atoi(arg) != 0)
		e = ft_strdup("INDIRECT");
	else if (ft_strchr(arg , SEPARATOR_CHAR))
		e = ft_strdup("SEPARATOR");
	else if (ft_strchr(arg, ':'))
		e = ft_strdup("LABEL");
	else
		e = ft_strdup("INSTRUCTION");
	ft_printf("Syntax error at token [TOKEN][%d:%d] %s \"%s\"\n", line_num + 1, colomn, e, arg);
	return (0);
}

int 		error_invalid_arg_type(t_t *command, int arg, int size)
{
	char 	*type;

	if (size == 1)
		type = ft_strdup("register");
	else if (size == 2)
		type = ft_strdup("direct");
	else
		type = ft_strdup("indirect");
	ft_printf("Invalid parameter %d type %s for instruction %s\n", arg, type, command->name_c);
	return (0);
}
 