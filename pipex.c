/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:20:05 by sdummett          #+#    #+#             */
/*   Updated: 2021/07/31 17:38:40 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Parser les arguments et les envoyer aux commandes respectives
*/

int	cmd2(int pipefd[], char *file, char **args)
{
	int		fd;
	int		fd2;

	close(pipefd[1]);
	fd = dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (fd < 0)
	{
		perror("dup2");
		return (1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("open");
		return (2);
	}
	fd2 = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (fd2 < 0)
	{
		perror("dup2");
		return (3);
	}
	if (execve(args[0], args, NULL) == -1)
	{
		perror(args[0]);
		return (4);
	}
	return (0);
}

int	cmd1(int pipefd[], char *file, char **args)
{
	int		fd;
	int		fd2;

	close(pipefd[0]);
	fd = dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (fd < 0)
	{
		perror("dup2");
		return (1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (2);
	}
	fd2 = dup2(fd, STDIN_FILENO);
	close(fd);
	if (fd2 < 0)
	{
		perror("dup2");
		return (3);
	}
	if (execve(args[0], args, NULL) == -1)
	{
		perror(args[0]);
		return (4);
	}
	return (0);
}

/*
** Gerer les retours des process ?
*/

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**get_all_paths(void)
{
	extern char	**__environ;
	char		**path;
	char		*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	while (__environ[i] != NULL)
	{
		tmp = ft_strnstr(__environ[i], "PATH=", 5);
		if (tmp != NULL)
			break;
		i++;
	}
	printf("tmp: |%s|\n", tmp);
	path = ft_split(tmp, ':');
	//	free(tmp);
	i = 0;
	while (path[i] != NULL)
	{
		printf("path[%d] : |%s|\n", i, path[i]);
		i++;
	}
	// free_paths(path);
	// return (path);
	return (NULL);
}

int	main(int ac, char **av)
{
	int			pid;
	int			pipefd[2];
	char		**args_cmd1;
	char		**args_cmd2;

	if (ac != 5)
	{
		printf("Error: Wrong number of args.\n");
		return (1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (2);
	}
	get_all_paths();
	
	int i = 0;
	args_cmd1 = ft_split(av[2], ' ');
	pid = fork();
	if (pid == 0)
		return (cmd1(pipefd, av[1],  args_cmd1));
	i = 0;
	args_cmd2 = ft_split(av[3], ' ');
	pid = fork();
	if (pid == 0)
		return (cmd2(pipefd, av[4], args_cmd2));
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	free(args_cmd1);
	free(args_cmd2);
	return (0);
}
