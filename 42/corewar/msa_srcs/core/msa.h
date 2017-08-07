/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:59:24 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/27 19:59:26 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSA_H
# define MSA_H

# define MEM_SIZE			(4*1024)

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)
# define FILE_MAX_SIZE		2874

# define REG_NUMBER			16
# define N_OP				16

# define T_REG				1
# define T_DIR				2
# define T_IND				4

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define UNUSED				0

typedef struct				s_content
{
	unsigned char			magic[4];
	char					prog_name[PROG_NAME_LENGTH + 4];
	char					prog_size[4];
	char					comment[COMMENT_LENGTH + 4];
	char					data[CHAMP_MAX_SIZE];
}							t_content;

struct s_wof;

typedef struct				s_parse
{
	char					*input_file;
	char					*output_file;
}							t_parse;

typedef struct				s_env
{
	struct s_wof			*wof;
	unsigned int			size;
	t_content				*content;
}							t_env;

typedef struct s_op			t_op;

struct						s_op
{
	char					*name;
	char					opcode;
	int						duration;
	int						param_nb;
	int						naocode[3];
	int						v_size;
	int						idx;
	int						(*fn)(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
};

const t_op					g_op_tab[N_OP];

int							parse(int argc, char **argv, t_parse *files);
t_content					*read_file(char *filename,
							unsigned int *total_size, char *c);
int							fill_output(t_env *env);
int							check_file(t_content *data);

int							extractor(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							check_bytecode(t_env *e, char *ptr, unsigned int l,
															const t_op *desc);

int							op_add(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_sub(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);

int							op_and(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_or(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_xor(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);

int							op_ld(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_lld(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_ldi(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_lldi(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);

int							op_fork(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_lfork(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);

int							op_st(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_sti(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);

int							op_live(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_zjmp(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);
int							op_aff(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc);

#endif
