/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 22:26:21 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 22:26:25 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

/*
** # define DEBUG_PARSE 		TRUE
** # define LABEL_DEBUG			TRUE
** # define WRITE_OP_DEBUG		TRUE
*/

# define U_SHORT				unsigned short
# define U_INT					unsigned int

# define OLD_SUFFIX 			".s"
# define NEW_SUFFIX 			".cor"
# define OLD_SUFFIX_SIZE 		2
# define NEW_SUFFIX_SIZE 		4

# define NAME_CMD_STRING		".name"
# define NAME_CMD_LENGTH		5
# define COMMENT_CMD_STRING		".comment"
# define COMMENT_CMD_LENGTH 	8

# define MEM_SIZE				(4*1024)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define T_REG					1
# define T_DIR					2
# define T_IND					4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

/*
** b = 4 + PROG_NAME_LENGTH + 1 + 4 + COMMENT_LENGTH + 1 + CHAMP_MAX_SIZE + 16
*/

# define BUFF_SIZE	(26 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE)

/*
** PERSONAL CONVENTION:
** Un champion pour etre valide doit posseder au moins 1 instruction.
*/

/*
** *name -> name asm of the instruction.
** n_params -> quantity of params that the instruction takes.
** params[3] -> list of available possible params.
** i -> Instruction op_code.
** turn -> NO CONSIDERED IN PROG ASM.
** *trad -> translation of op into french
** o_code -> if TRUE, 'octet de codage' have to written.
** (FALSE; no 'octet de codage');
** v_size -> if TRUE, direct and indirect var take 2 bytes.
** (FALSE: indirect = 4 && direct == 2)
*/

typedef struct		s_op
{
	char			*name;
	int				n_params;
	int				params[3];
	char			i;
	int				turn;
	char			*trad;
	int				o_code;
	int				v_size;
}					t_op;

/*
** magic -> four byte magic_code.
** prog_name -> name of challenger.
** prog_size -> total size of instruction segment.
** comment -> comment for the challenger.
*/

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

/*
** *name -> Nom du label découvert.
** origin -> Utilisé pour décrire l'origine d'un label, son pc de base.
** jmp_value -> Utilisé comme lien vers un label.
** size -> special size of data got labels, must be 2 or 4.
*/

typedef struct		s_label
{
	char			*name;
	U_SHORT			origin;
	U_SHORT			jmp_value;
	int				size;
}					t_label;

/*
** hook -> special pour les comment or name multiline.
** name -> Devient TRUE quand le champ .name a été lu.
** comment -> Devient TRUE quand le champ .comment a été lu.
** active -> Indique qu'au moins un processus de lecture/écriture
** d'instruction a été écrit.
** label_map -> Liste chainée des différents labels trouvés
** dans le fichier source.
** buff -> Désigne le buffer entier à écrire.
** origin_op -> Pointeur sur le début de l'instruction en cours de traitement.
** ptr -> Pointeur courant sur l'operation en cours.
** (devra être ajusté de + 0xFE56)
*/

typedef struct		s_map
{
	int				hook;
	int				name;
	int				comment;
	int				active;
	t_list			*label_map;
	char			*buff;
	char			*origin_op;
	char			*ptr;
}					t_map;

typedef struct		s_fn
{
	char			l;
	char			*(*f)(char *content, t_map *map, t_op *op, int n);
	char			flag;
}					t_fn;

/*
** parse_center.c:
** global treatement of input data loaded by get_next_line.
*/

int					parse_center(char *line, t_header *header, t_map *map,
																		int n);

/*
** labels.c:
** All toools for label assignation in bytecode.
*/

int					manage_label_modifications(t_map *map);
int					test_label_at_first(char *line, t_map *map);
char				*assign_label_jump(char *s, t_map *map, int size);
void				del_label(void *container, size_t size);

/*
** common.c:
** just raw tools.
*/

char				*clean_content_memory(char **content, char *err);
unsigned int		l2b(unsigned int a);
void				write_direct_value(char *s, int n, int x);
int					debug_result (t_map *map);
int					is_label_char(char c);

/*
** parse_line.c.
** Manage parsing of instructions.
*/

int					extract_instruction(char *line, t_map *map, int n);

/*
** write_instruction.c
** Convert instruction to bytecode.
*/

char				*write_instruction(char *line, t_op *op, t_map *map);

/*
** trim_strsplit.c
** Split a line without space ou tab.
*/

char				**trim_strsplit(char const *s, char c, int *size);

/*
** get_next_line.c:
** Read input file line by line.
*/

int					n_get_trim_line(int const fd, char **line, int trimed);
void				clear_fd_queue(int const fd, char **line, int argc);

/*
**  secure_atoi.c.
** extract an int from char to int.
*/

int					secure_atoi(const char *nptr, int *error);

void				secure_lst(t_list **alst, t_list *new);

#endif
