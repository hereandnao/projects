/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 22:10:03 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 22:10:07 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR				"{red}ERROR:{yellow}"
# define WAR				"{yellow}"
# define EOL				"{eoc}\n"

# define IF					"input file"
# define ASS				"assignation"
# define LOC				"allocation"
# define TOV				"This type of value"
# define WHS				"when splitting"

# define ERR_MISSING_FILE	ERR "Please give me a file" EOL
# define ERR_SUMARY			ERR "There are something wrong in %s" EOL
# define ERR_EXTEND			WAR "Extend of "IF" is incorect. Give me a .s" EOL

# define ERR_NAME			WAR	"No champion name or malformed name !" EOL
# define ERR_COMMENT		WAR	"No comment or malformed comment !" EOL
# define ERR_VOID			WAR	"There is no instruction in that champion !" EOL

# define ERR_TOO_BIG		WAR	"This champion is too big !" EOL
# define ERR_NO_NAME		WAR "That champion has no a epic name !" EOL

# define ERR_BIG_COMMENT	WAR	"Comment is very too long !" EOL
# define ERR_BIG_NAME		WAR	"Name is very too long !" EOL
# define ERR_RAW_NAME		WAR	"There are garbage around name !" EOL
# define ERR_RAW_COMMENT	WAR	"Thera are garbage around comment !" EOL

/*
** Errors list in parse_line.c:
*/

# define ERR_OP			 	WAR "%s\nL%i -> Unknown instruction !" EOL

/*
** Errors list in write_instruction.c:
*/

# define ERR_SPLIT			WAR "%s\nL%i -> Memory "LOC" error "WHS" !" EOL
# define ERR_N_PARAMS		WAR	"%s\nL%i -> Bad number of params !" EOL
# define ERR_REG			WAR	"%s\nL%i -> Malformed Register writting !" EOL
# define ERR_PARAM_CKECK  	WAR	"%s\nL%i -> "TOV" is forbidden here !" EOL
# define ERR_ATOI		 	WAR	"%s\nL%i -> Not a a right number writting !" EOL

/*
** Errors in Labels.c
*/

# define ERR_LABEL_ASSIGN	WAR	"Unknown symbol %s\nLabel "ASS" failed !" EOL
# define ERR_LABEL_JUMP		WAR "%s\nL%i -> "ASS" of that label failed !" EOL

# define BAD_ALLOCATION		WAR	"%s\nL%i -> Fatal error when memory "LOC" !" EOL

#endif
