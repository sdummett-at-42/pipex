/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stone <stone@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 02:12:37 by stone             #+#    #+#             */
/*   Updated: 2021/08/12 18:09:04 by stone            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_path(char *path, t_path *path_type)
{
	int	i;

	path_type->is_absolute = false;
	path_type->is_relative = false;
	path_type->is_dot_slash = false;
	if (path[0] == '/')
	{
		path_type->is_absolute = true;
		return ;
	}
	if (path[0] == '.' && path[1] == '/')
	{
		path_type->is_relative = true;
		path_type->is_dot_slash = true;
		return ;
	}
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
		{
			path_type->is_relative = true;
			return ;
		}
		i++;
	}
}

void	exec_cmd(char **args, char **path)//char *args_to_parse)
{
	t_path	path_type;
	// char	**args;
	// char	**path;
	int		i;

	// args = ft_split(args_to_parse, ' ');
	// path = get_paths(*args);
	 check_path(args[0], &path_type);
	if (path_type.is_relative || path_type.is_absolute)
	{
		if (path_type.is_dot_slash)
			execve(args[0] + 2, args, NULL);
		else
			execve(args[0], args, NULL);
	}
	else
	{
		i = 0;
		while (path[i] != NULL)
		{
			execve(path[i], args, NULL);
			i++;
		}
	}
	perror(args[0]);
}
