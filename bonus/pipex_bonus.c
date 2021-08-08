/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:52:43 by stone             #+#    #+#             */
/*   Updated: 2021/08/09 00:27:29 by stone            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	exec_cmd(int pipein, int pipeout)
{
	int	value;
	read(pipein, &value, sizeof(int));
	close(pipein);
	printf("Hello i'm a child process\n");
	printf("The value read is %d\n", value);
	value = value + 1;
	write(pipeout, &value, sizeof(int));
	close(pipeout);
	return (0);
}

int main()
{
	int	pipefd1[2];
	int pipefd2[2];
	int	pid;
	int	i;
	int x = 42;

	if (pipe(pipefd1) < 0)
	{
		perror("pipe");
		return (1);
	}
	write(pipefd1[1], &x, sizeof(int));
	close(pipefd1[1]);

	i = 0;
	while (i < 5)
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
			return (exec_cmd(pipefd1[0], pipefd2[1]));
		close(pipefd1[0]);
		close(pipefd2[1]);
		pipefd1[0] = pipefd2[0];
		i++;
	}
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
	return (0);
}
