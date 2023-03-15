/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:04:58 by apereira          #+#    #+#             */
/*   Updated: 2023/03/15 15:59:51 by apereira         ###   ########.fr       */
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
	ft_printf("Command not found: %s\n", argv);
	return (NULL);
}

// Opens the first file FD, parses the first command by duplicating it
// and executes it. Passes the output onto the next command instead of
// to the standard output.
void	first_process(t_vars *vars, char **argv, char **envp, int *pipe_fd)
{
	vars->fd1 = open(argv[1], O_RDONLY);
	if (vars->fd1 < 0)
	{
		perror("Infile");
		return ;
	}
	vars->pid1 = fork();
	if (vars->pid1 < 0)
		return ;
	if (vars->pid1 == 0)
	{
		vars->cmd1_path = check_valid_cmd(vars->cmd1_flags[0], envp);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		dup2(vars->fd1, STDIN_FILENO);
		vars->cmd1_path = check_valid_cmd(vars->cmd1_flags[0], envp);
		if (!vars->cmd1_path)
			return ;
		execve(vars->cmd1_path, vars->cmd1_flags, envp);
	}
}

// Opens the second file FD, parses the second command by duplicating it
// and executes it. Passes the output onto the second file instead of
// to the standard output.
// O_TRUNC deletes file contents so we can write to the file, O_CREAT creates 
// a file if there isn't one available, O_RDWR opens a FD to read and write.
// The number sets the perms of the file so it can be read from and wrote on.
void	second_process(t_vars *vars, char **argv, char **envp, int *pipe_fd)
{
	vars->fd2 = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (vars->fd2 < 0)
	{
		perror("Outfile");
		return ;
	}
	vars->pid2 = fork();
	if (vars->pid2 < 0)
		return ;
	if (vars->pid2 == 0)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close (pipe_fd[1]);
		dup2(vars->fd2, STDOUT_FILENO);
		vars->cmd2_path = check_valid_cmd(vars->cmd2_flags[0], envp);
		if (!vars->cmd2_path)
			return ;
		execve(vars->cmd2_path, vars->cmd2_flags, envp);
	}
}

// 
int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		pipe_fd[2];

	if (argc != 5)
	{
		write(2, "Invalid number of arguments.\n", 30);
		return (1);
	}
	if (pipe(pipe_fd) < 0)
	{
		perror("Pipe");
		exit(1);
	}
	vars.cmd1_flags = ft_split(argv[2], ' ');
	vars.cmd2_flags = ft_split(argv[3], ' ');
	first_process(&vars, argv, envp, pipe_fd);
	second_process(&vars, argv, envp, pipe_fd);
	close (pipe_fd[0]);
	close (pipe_fd[1]);
	waitpid(vars.pid1, NULL, 0);
	waitpid(vars.pid2, NULL, 0);
	clean_program(&vars);
}
