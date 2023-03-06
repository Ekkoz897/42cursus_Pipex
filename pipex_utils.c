/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 07:39:17 by apereira          #+#    #+#             */
/*   Updated: 2023/03/06 12:15:11 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}

// Finds the PATH string in the "env" text
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

// Frees all the mallocs
void	clean_program(t_vars *vars)
{
	ft_free (vars->cmd1_flags);
	ft_free (vars->cmd2_flags);
	free (vars->cmd1_path);
	free (vars->cmd2_path);
	close (vars->fd1);
	close (vars->fd2);
}
