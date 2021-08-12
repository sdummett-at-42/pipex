/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:52:43 by stone             #+#    #+#             */
/*   Updated: 2021/08/12 16:22:23 by stone            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	cmd(int pipein, int pipeout, char *cmd)
{
	int	fdin;
	int	fdout;

	fdin = dup2(pipein, STDIN_FILENO);
	close(pipein);
	if (fdin < 0)
	{
		perror("dup2");
		return (1);
	}
	fdout = dup2(pipeout, STDOUT_FILENO);
	close(pipeout);
	if (fdout < 0)
	{
		perror("dup2");
		return (2);
	}
	exec_cmd(cmd);
	perror(cmd);
	close(fdout);
	printf("quit\n");
	return (2);
}

void	create_heredoc(char *limiter)
{
	char	*heredoc;
	char	*line;
	char	*tmp;
	int		len;
	int		fd;

	(void)limiter;
	heredoc = ft_strjoin("", "");
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		get_next_line(0, &line);
		if (ft_strlen(line) > ft_strlen(limiter))
			len = ft_strlen(line);
		else
			len = ft_strlen(limiter);
		if (ft_strncmp(line, limiter, len) == 0)
		{
			free(line);
			break ;
		}
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, line);
		free(line);
		free(tmp);
		tmp = heredoc;
		heredoc = ft_strjoin(heredoc, "\n");
		free(tmp);
	}
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	write(fd, heredoc, ft_strlen(heredoc));
	close(fd);
	free(heredoc);
}

void	heredoc(char *limiter, char *cmd1, char *cmd2, char *outfile)
{
	int	fd_heredoc;
	int	fd_out;
	int	pipefd[2];
	int	pid;
	int	i;

	create_heredoc(limiter);
	fd_heredoc = open(".heredoc", O_RDONLY);
	if (fd_heredoc < 0)
	{
		perror("open");
		return ;
	}
	fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd_out < 0)
	{
		perror("open");
		return ;
	}
	pipe(pipefd);
	if (pipefd < 0)
	{
		perror("pipe");
		return ;
	}
	i = 0;
	while (i < 2)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			if (i == 0)
			{
				cmd(fd_heredoc, pipefd[1], cmd1);
				exit(1);
			}
			else
			{
				cmd(pipefd[0], fd_out, cmd2);
				exit(1);
			}
		}
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd_heredoc);
	close(fd_out);
	wait(NULL);
	unlink(".heredoc");
}

int	main(int ac, char **av)
{
	int	pipefd1[2];
	int	pipefd2[2];
	int	infilefd;
	int	outfilefd;
	int	pid;
	int	i;

	if (ac < 5)
	{
		printf("Error: Wrong number of args.\n");
		return (1);
	}
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		if (ac != 6)
		{
			printf("Error: Wrong numner of args(heredoc)\n");
			return (1);
		}
		heredoc(av[2], av[3], av[4], av[5]);
		return (0);
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
		return (3);
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
				return (cmd(infilefd, pipefd2[1], av[i + 1]));
			else if (i == ac - 3)
				return (cmd(pipefd1[0], outfilefd, av[i + 1]));
			else
				return (cmd(pipefd1[0], pipefd2[1], av[i + 1]));
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
