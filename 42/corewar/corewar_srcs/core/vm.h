/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:25:58 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/22 22:29:56 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define MAX_PLAYERS			4
# define MIN_PLAYERS			1
# define MEM_SIZE				(4*1024)
# define MEM_MASK				0xFFF
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define FILE_MAX_SIZE			2874

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define N_OP					16

# define T_REG					1
# define T_DIR					2
# define T_IND					4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define UNUSED					0

/*
** Structure of a warrior as it appears in the .COR file:
** Prog_name -> Warrior's name
** Prog size/comment/data -> its size, comm and code of the warrior
** This structure will be stored in the t_warrior struct
** itself contained in the t_env struc.
*/

struct s_list;
struct s_pa;

typedef struct				s_content
{
	unsigned char			magic[4];
	char					prog_name[PROG_NAME_LENGTH + 4];
	char					prog_size[4];
	char					comment[COMMENT_LENGTH + 4];
	char					data[CHAMP_MAX_SIZE];
}							t_content;

typedef struct				s_warrior
{
	t_content				file;
	int						number;
}							t_warrior;

typedef struct				s_champ_num
{
	char					*name;
	int						nb;
}							t_champ_num;
/*
** Structure of a process:
** owner -> Owner of the process.
** pc -> Program Counter : Location of the process.
** countDown -> Time before next operation.
** live -> Count of lives in a round
** protection -> When a child was born from a parent who has made a live,
** he survives the current round.
** reg -> Memory of a process.
** carry -> carry
** fn -> functin pointer of the current instruction to do.
*/

typedef struct s_process	t_process;
typedef struct s_env		t_env;

struct						s_process
{
	t_warrior				*owner;
	int						pc;
	int						countdown;
	int						live;
	int						protection;
	int						reg[REG_NUMBER];
	int						carry;
	int						nb;
	void					(*fn)(t_env *, t_process *);
	t_process				*next;
};

typedef enum				e_flags
{
	GRAPHIC = 0x04,
	DUMP = 0x02,
	VERBOSE = 0x01
}							t_flags;

/*
** Structure of the environment :
** nb_players = number of players loaded
** warriors = see above
** dump_value = number given with the -d flag
** nb_process = number of created processes so far
*/

struct						s_env
{
	char					map[4096];
	struct s_pa				*pa;
	int						nb_players;
	struct s_list			*warriors;
	t_flags					flags;
	t_process				*process;
	t_warrior				*last_live;
	int						dump_value;
	int						nb_cycle;
	int						nb_process;
	void					(*fn[16])(struct s_env *, t_process *);
};

typedef struct				s_op
{
	char					*name;
	char					opcode;
	int						duration;
	int						param_nb;
	int						naocode[3];
	int						v_size;
	int						idx;
	void					(*fn)(t_env *, t_process *);
}							t_op;

typedef struct				s_highway
{
	unsigned char			nb;
	int						tmp;
	t_env					*e;
	t_process				*p;
}							t_highway;

const t_op					g_op_tab[N_OP];

t_warrior					*read_file(char *file_name,
											unsigned int *total_size, char *c);

struct s_list				*parsing(int argc, char **argv, t_env *e);
void						display_map(char map[4096]);
void						manage_champions(t_env *env);
unsigned int				get_real_size(char prog_size[4]);
int							check_file(t_content *data);
struct s_list				*err_bad_size(struct s_list *lst);
struct s_list				*free_t_list(struct s_list *lst);

int							destroy_process(t_process **lst);
void						create_process(t_warrior *warrior, int pc,
													t_process **lst, t_env *e);
void						clone_process(t_process **lst, t_process *process,
																	t_env *e);
int							free_all_process(t_process **lst);

void						time_machine(t_env *e);

void						op_add(t_env *e, t_process *process);
void						op_sub(t_env *e, t_process *process);

void						op_and(t_env *e, t_process *process);
void						op_or(t_env *e, t_process *process);
void						op_xor(t_env *e, t_process *process);

void						op_ld(t_env *e, t_process *process);
void						op_lld(t_env *e, t_process *process);
void						op_ldi(t_env *e, t_process *process);
void						op_lldi(t_env *e, t_process *process);

void						op_fork(t_env *e, t_process *process);
void						op_lfork(t_env *e, t_process *process);

void						op_st(t_env *e, t_process *process);
void						op_sti(t_env *e, t_process *process);

void						op_live(t_env *e, t_process *process);
void						op_zjmp(t_env *e, t_process *process);
void						op_aff(t_env *e, t_process *process);

int							extractor(int tab[3], t_env *e, t_process *process,
																		int n);

int							extract_dir(t_process *process,
								char field[MEM_SIZE], int *offset, int v_size);
int							extract_ind(t_process *process,
								char field[MEM_SIZE], int *offset, int idx_mod);
int							get_nb(char *bf, int pc);
int							get_reg_value(char *bf, t_process *process,
													int *offset, int *error);

#endif
