/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:05:05 by apereira          #+#    #+#             */
/*   Updated: 2023/03/06 16:05:18 by apereira         ###   ########.fr       */
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

// Util functions
void	ft_free(char **array);
void	clean_program(t_vars *vars);
char	*find_path(char **envp);

#endif
