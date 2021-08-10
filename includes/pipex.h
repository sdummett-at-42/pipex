/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:20:39 by sdummett          #+#    #+#             */
/*   Updated: 2021/08/10 01:05:22 by stone            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> //<- to delete 
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>

char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *b, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	rm_n_first_char(char **str, int n);
char	**get_paths(char *cmd);
void	exec_cmd(char *args_to_parse);

typedef struct s_path
{
	bool	is_absolute;
	bool	is_relative;
	bool	is_dot_slash;
}	t_path;

#endif