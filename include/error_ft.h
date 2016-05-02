/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scollon <scollon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:49:19 by scollon           #+#    #+#             */
/*   Updated: 2016/05/01 11:12:49 by scollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_FT_H
# define ERROR_FT_H

# include <errno.h>
# include <stdlib.h>

/*
**	DEFINE USE TO PRINT ERROR_TYPE
*/
# define E_MLX_INIT		"mlx_init() failed"
# define E_WIN_INIT 	"window initialisation failed"
# define E_IMG_INIT 	"image initialisation failed"

# define E_CINIT 		"camera initialisation failed"
# define E_CPARAM 		"invalid camera parameter"

# define E_LINIT		"light initialisation failed"
# define E_LTYPE		"invalid light type"
# define E_STYPE		"invalid shadow type"
# define E_LPARAM		"invalid light parameter"

# define E_OINIT 		"object initialisation failed"
# define E_OTYPE 		"invalid object type"
# define E_OPARAM 		"invalid object parameter"

# define E_ARG 			"invalid argument"
# define E_MALLOC 		"malloc() failed"
# define E_IFILE		"invalid file format"
# define E_SEMPTY		"scene must have cameras, objects and lights"

# define ERR_FILE_FLAGS O_WRONLY | O_CREAT | O_APPEND
# define ERR_FILE_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

/*
**	FUNCTION ERROR
**	free environnement, print "rt : ERROR_TYPE : ERROR_SOURCE\n"
**	and exit if exit is set at 1
*/

#endif
