/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:05:05 by apereira          #+#    #+#             */
/*   Updated: 2023/03/06 07:43:06 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "Get_next_line/get_next_line.h"

typedef struct s_vars
{
	int		fd[2];
	int		pid1;
	int		pid2;
	int		fd1;
	int		fd2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_flags;
	char	**cmd2_flags;
}t_vars;

void	clean_program(char **argv, t_vars *vars);

#endif
