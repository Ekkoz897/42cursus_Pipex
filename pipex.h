/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:05:05 by apereira          #+#    #+#             */
/*   Updated: 2023/02/28 16:55:39 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <fcntl.h>
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
	char	*cmd_path1;
	char	*cmd_path2;
	char	**cmd_flags1;
	char	**cmd_flags2;
}t_vars;

#endif
