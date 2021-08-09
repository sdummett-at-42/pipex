/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:52:43 by stone             #+#    #+#             */
/*   Updated: 2021/08/09 03:29:43 by stone            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	exec_cmd(int pipein, int pipeout, char *cmd)
{
	int fdin;
	int fdout;
	char *tab[2]; // <- temporary

	fdin = dup2(pipein, STDIN_FILENO);
	close(pipein);
	if (fdin < 0)
	{
		perror("dup2");
		return(1);
	}
	fdout = dup2(pipeout, STDOUT_FILENO);
	close(pipeout);
	if (fdout < 0)
	{
		perror("dup2");
		return (2);
	}
	tab[0] = cmd;
	tab[1] = NULL;
	fflush(stdout);
	execve(cmd, tab, NULL);
	perror(cmd);
	close(fdout);
	return (2);
}

int main(int ac, char **av)
{
	int	pipefd1[2];
	int pipefd2[2];
	int	infilefd;
	int	outfilefd;
	int	pid;
	int	i;

	if (ac < 5)
	{
		printf("Error : Wrong number of args.\n");
		return (1);
	}
	infilefd = open(av[1], O_RDONLY);
	if (infilefd < 0)
	{
		perror("open");
		return (3);
	}
	outfilefd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfilefd < 0)
	{
		perror("open");
		return(3);
	}
	i = 1;
	while (i < ac - 2)
	{
		pipe(pipefd2);
		if (pipefd2 < 0)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (2);
		}
		if (pid == 0)
		{
			if (i == 1)
				return (exec_cmd(infilefd, pipefd2[1], av[i + 1]));
			else if (i == ac - 3)
				return (exec_cmd(pipefd1[0], outfilefd, av[i + 1]));
			else
				return (exec_cmd(pipefd1[0], pipefd2[1], av[i + 1]));
		}
		close(pipefd1[0]);
		close(pipefd2[1]);
		pipefd1[0] = pipefd2[0];
		i++;
	}
	close(infilefd);
	close(outfilefd);
	while (i > 1)
	{
		wait(NULL);
		i--;
	}
	return (0);
}
