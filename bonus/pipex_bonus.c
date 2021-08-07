/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:52:43 by stone             #+#    #+#             */
/*   Updated: 2021/08/08 00:16:47 by stone            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	exec_cmd(int pipefd[1][2])
{
	int	value;
	(void)pipefd;
	read(pipefd[0][0], &value, sizeof(int));
	printf("Hello i'm a child process\n");
	printf("The value read is %d\n", value);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	return (0);
}

int main()
{
	int	pipefd[1][2];
	int	pid;
	int	i;
	int x = 42;
	i = 0;
	while (i < 1)
	{
		pipe(pipefd[0]);
		if (pipefd[0] < 0)
		{
			perror("pipe");
			return (1);
		}
		if (i == 0)
			write(pipefd[0][1], &x, sizeof(int));
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (2);
		}
		if (pid == 0)
			return (exec_cmd(&pipefd[0]));
		close(pipefd[0][0]);
		i++;
	}
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
	return (0);
}