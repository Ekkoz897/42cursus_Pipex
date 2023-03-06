/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:04:58 by apereira          #+#    #+#             */
/*   Updated: 2023/03/06 13:47:23 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Checks if the command received in ARGV is valid by
// searching for it in the bin folder
char	*check_valid_cmd(char *argv, char **envp)
{
	int		i;
	char	**split_paths;
	char	*path;
	char	*temp;
	char	*cmd;

	cmd = find_path(envp);
	split_paths = ft_split(cmd, ':');
	i = 0;
	while (split_paths[i])
	{
		temp = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(temp, argv);
		free (temp);
		if (access(path, 0) == 0)
		{
			ft_free(split_paths);
			return (path);
		}
		free (path);
		i++;
	}
	ft_free (split_paths);
	return (NULL);
}

// Opens the first file FD, parses the first command by duplicating it
// and executes it. Passes the output onto the next command instead of
// to the standard output.
int	first_process(t_vars *vars, char **argv, char **envp, int *pipe_fd)
{
	vars->fd1 = open(argv[1], O_RDONLY);
	if (vars->fd1 < 0)
	{
		return (0);
		ft_printf("Error, the 1st file is invalid\n");
	}
	vars->cmd1_path = check_valid_cmd(vars->cmd1_flags[0], envp);
	if (!vars->cmd1_path)
	{
		ft_printf("Error, 1st command is invalid\n");
		return (0);
	}
	vars->pid1 = fork();
	if (vars->pid1 < 0)
		return (0);
	if (vars->pid1 == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		dup2(vars->fd1, STDIN_FILENO);
		execve(vars->cmd1_path, vars->cmd1_flags, envp);
	}
	return (1);
}

// Opens the second file FD, parses the second command by duplicating it
// and executes it. Passes the output onto the second file instead of
// to the standard output.
int	second_process(t_vars *vars, char **argv, char **envp, int *pipe_fd)
{
	vars->fd2 = open(argv[4], O_RDWR);
	if (vars->fd2 < 0)
	{
		ft_printf("Error, the 2nd file is invalid\n");
		return (0);
	}
	vars->cmd2_path = check_valid_cmd(vars->cmd2_flags[0], envp);
	if (!vars->cmd1_path)
	{
		ft_printf("Error, 2nd command is invalid\n");
		return (0);
	}
	vars->pid2 = fork();
	if (vars->pid2 < 0)
		return (0);
	if (vars->pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close (pipe_fd[1]);
		dup2(vars->fd2, STDOUT_FILENO);
		execve(vars->cmd2_path, vars->cmd2_flags, envp);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		pipe_fd[2];

	if (argc != 5)
		return (ft_printf("Error, there should be 5 arguments\n"));
	if (pipe(pipe_fd) < 0)
		return (ft_printf("Error, PIPE"));
	vars.cmd1_flags = ft_split(argv[2], ' ');
	vars.cmd2_flags = ft_split(argv[3], ' ');
	first_process(&vars, argv, envp, pipe_fd);
	second_process(&vars, argv, envp, pipe_fd);
	waitpid(vars.pid1, NULL, 0);
	waitpid(vars.pid2, NULL, 0);
	clean_program(&vars);
}
