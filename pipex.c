/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:20:05 by sdummett          #+#    #+#             */
/*   Updated: 2021/08/05 14:33:55 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Parser les arguments et les envoyer aux commandes respectives
*/

int	cmd2(int pipefd[], char *file, char **args, char **path)
{
	int	fd;
	int	fd2;
	int	i;

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
	i = 0;
	while (path[i] != NULL)
	{
		execve(path[i], args, NULL);
		i++;
	}
	perror(args[0]);
	return (4);
}

int	cmd1(int pipefd[], char *file, char **args, char **path)
{
	int	fd;
	int	fd2;
	int	i;

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
	i = 0;
	while (path[i] != NULL)
	{
		execve(path[i], args, NULL);
		i++;
	}
	perror(args[0]);
	return (4);
}

/*
** Gerer les retours des process ?
*/


int	main(int ac, char **av)
{
	int			pid;
	int			pipefd[2];
	char		**args_cmd1;
	char		**args_cmd2;
	char		**path_cmd1;
	char		**path_cmd2;

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
	args_cmd1 = ft_split(av[2], ' ');
	path_cmd1 = get_paths(*args_cmd1);
	pid = fork();
	if (pid == 0)
		return (cmd1(pipefd, av[1],  args_cmd1, path_cmd1));
	args_cmd2 = ft_split(av[3], ' ');
	path_cmd2 = get_paths(*args_cmd2);
	pid = fork();
	if (pid == 0)
		return (cmd2(pipefd, av[4], args_cmd2, path_cmd2));
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);	
	free(args_cmd1);
	free(path_cmd1);
	free(args_cmd2);
	free(path_cmd2); // <- free all the pointer inside path_cmd[1-2]
	return (0);
}
