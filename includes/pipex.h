/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:20:39 by sdummett          #+#    #+#             */
/*   Updated: 2021/08/03 20:54:28 by stone            ###   ########.fr       */
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

char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *b, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	rm_n_first_char(char **str, int n);


#endif