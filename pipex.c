/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:04:58 by apereira          #+#    #+#             */
/*   Updated: 2023/02/28 17:28:37 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// /nfs/homes/apereira/.bun/bin
// /nfs/homes/apereira/bin
// /usr/local/sbin
// /usr/sbin
// /sbin
// /bin
// /usr/games
// /usr/local/games
// /snap/bin

char	*check_valid_cmd(char *argv, char **env)
{
	int		i;
	char	**split_paths;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=/"))
		{
			split_paths = ft_split(env[i], ':');
			i = 0;
			while (split_paths[i])
			{
				path = ft_strjoin(split_paths[i], argv);
				if (access(path, X_OK))
					return (split_paths[i]);
				i++;
			}
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	if (argc != 4)
		return (0);
	argv[1] = ft_strjoin("./", argv[1]);
	argv[4] = ft_strjoin("./", argv[4]);
	vars.fd1 = open(argv[1], O_RDONLY);
	vars.fd1 = open(argv[4], O_RDONLY);
	vars.cmd_flags1 = ft_split(argv[2], ' ');
	vars.cmd_flags2 = ft_split(argv[3], ' ');
	vars.cmd_path1 = check_valid_cmd(vars.cmd_flags1[0], env);
	vars.cmd_path2 = check_valid_cmd(vars.cmd_flags2[0], env);
}
