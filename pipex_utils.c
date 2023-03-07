/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 07:39:17 by apereira          #+#    #+#             */
/*   Updated: 2023/03/07 17:49:06 by apereira         ###   ########.fr       */
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
	free (array);
}

// Finds the PATH string in the "envp" text
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
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
