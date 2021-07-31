/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:20:05 by sdummett          #+#    #+#             */
/*   Updated: 2021/07/31 01:06:18 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Parser les arguments et les envoyer aux commandes respectives
*/

int	cmd2(int pipefd[], char *file)
{
	int		fd;
	int		fd2;
	char	*args[] = {"grep", "s", NULL};

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
		printf("Error hwewn\n");
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
	if (execve("/usr/bin/grep", args, NULL) == -1)
	{
		perror("cmd2");
		return (4);
	}
	return (0);
}

int	cmd1(int pipefd[], char *file)
{
	int		fd;
	int		fd2;
	char	*args[] = {"cat", NULL};

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
	if (execve("/usr/bin/cat", args, NULL) == -1)
	{
		perror("cmd1");
		return (4);
	}
	return (0);
}

/*
** Gerer les retours des process ?
*/

int	main(int ac, char **av)
{
	int	pid;
	int	pipefd[2];

	(void)ac; // unvoid these later
	(void)av;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
		return (cmd1(pipefd, "infile"));
	pid = fork();
	if (pid == 0)
		return (cmd2(pipefd, "outfile"));
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
