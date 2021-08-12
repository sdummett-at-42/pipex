/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:58:17 by stone             #+#    #+#             */
/*   Updated: 2021/08/12 18:22:31 by stone            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h> // <- to remove
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>

void	exec_cmd(char **args, char **path);
char	**ft_split(char const *s, char c);
char	**get_paths(char *cmd);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *b, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	rm_n_first_char(char **str, int n);
int		ft_strncmp(const char *str1, const char *str2, size_t count);
int		ft_strlen(char *str);
int		get_next_line(int fd, char **line);
void	free_args_path(char **args, char **path);

typedef struct s_path
{
	bool	is_absolute;
	bool	is_relative;
	bool	is_dot_slash;
}	t_path;

#endif