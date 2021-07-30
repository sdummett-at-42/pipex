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



int	execcmd2(int pipefd[], char *file)
{
	int		fd;
	int		fd2;
	char	*args[] = {"grep", "s", NULL};

	close(pipefd[1]);
	printf("---pipefd[0]: %d\n", pipefd[0]);
	fd = dup2(pipefd[0], STDIN_FILENO);
	printf("---pipefd[0]fd: %d\n", fd);
	close(pipefd[0]);
	pipefd[0] = fd;

	printf("execcmd1\n");
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		printf("Error hwewn\n");
		perror("open");
		return (1);
	}
	fd2 = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (fd2 < 0)
	{
		perror("dup2");
		return (2);
	}

	// Pipes
	


	//

	if (execve("/usr/bin/grep", args, NULL) == -1)
	{
		perror("cmd2");
		return (3);
	}
	return (0);
}

int execcmd1(int pipefd[], char *file)
{
	int		fd;
	int		fd2;
	char	*args[] = {"cat", NULL};

	printf("pipefd[0]: %d\n", pipefd[0]);
	printf("pipefd[1]: %d\n", pipefd[1]);

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("file is |%s|\n", file);
		printf("Error hwesdffsdn\n");
		perror("open");
		return (1);
	}
	fd2 = dup2(fd, STDIN_FILENO);
	close(fd);
	if (fd2 < 0)
	{
		perror("dup2");
		return (2);
	}

	// Pipes
	
	close(pipefd[0]);
	fd = dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	pipefd[1] = fd;
	//

	if (execve("/usr/bin/cat", args, NULL) == -1)
	{
		perror("cmd1");
		return (3);
	}
	return (0);
}

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
	printf("--pefd[0]: %d\n", pipefd[0]);
	printf("--pefd[1]: %d\n", pipefd[1]);
	pid = fork();
	if (pid == 0)
	{
		// Child process 2 [ cmd2 ]
		return (execcmd1(pipefd, "infile"));
	}

	pid = fork();
	if (pid == 0)
	{
		// Child process 1 [ cmd1 ]
		return (execcmd2(pipefd, "outfile"));
		// 
	}

	wait(NULL);
	wait(NULL);
	return (0);
}