/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:04:58 by apereira          #+#    #+#             */
/*   Updated: 2023/03/06 07:42:32 by apereira         ###   ########.fr       */
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
			ft_free (split_paths);
			return (path);
		}
		free (path);
		i++;
	}
	ft_free (split_paths);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		pipe_fd[2];

	if (argc != 5)
		return (ft_printf("Error, wrong number of arguments\n"));
	if (pipe(pipe_fd) < 0)
		return (ft_printf("Error, PIPE"));
	argv[1] = ft_strjoin("./", argv[1]);
	argv[4] = ft_strjoin("./", argv[4]);
	//
	vars.fd1 = open(argv[1], O_RDONLY);
	if (vars.fd1 < 0)
		return (ft_printf("Error, the 1st file is invalid\n"));
	vars.cmd1_flags = ft_split(argv[2], ' ');
	vars.cmd1_path = check_valid_cmd(vars.cmd1_flags[0], envp);
	if (!vars.cmd1_path)
		return (ft_printf("Error, 1st command is invalid\n"));
	vars.pid1 = fork();
	if (vars.pid1 < 0)
		exit (0);
	if (vars.pid1 == 0)
	{
		dup2(vars.fd1, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		close (pipe_fd[1]);
		execve(vars.cmd1_path, vars.cmd1_flags, envp);
	}
	// waitpid(vars.pid1, NULL, 0);
	//
	vars.fd2 = open(argv[4], O_RDWR);
	if (vars.fd1 < 0)
		return (ft_printf("Error, the 2nd file is invalid\n"));
	vars.cmd2_flags = ft_split(argv[3], ' ');
	vars.cmd2_path = check_valid_cmd(vars.cmd2_flags[0], envp);
	if (!vars.cmd1_path)
		return (ft_printf("Error, 2nd command is invalid\n"));
	vars.pid2 = fork();
	if (vars.pid2 < 0)
		exit (0);
	if (vars.pid2 == 0)
	{
		dup2(vars.fd2, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		close (pipe_fd[1]);
		execve(vars.cmd2_path, vars.cmd2_flags, envp);
	}
	// waitpid(vars.pid2, NULL, 0);
	//
	clean_program(argv, &vars);
}
