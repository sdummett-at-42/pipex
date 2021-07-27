/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 01:02:32 by sdummett          #+#    #+#             */
/*   Updated: 2021/07/28 01:13:24 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int pid = fork();
	if (pid == -1)
		return 1;
		
	if (pid == 0)
	{
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
		printf("THIS NOT PRINT ON THEN TERMINAL!\n");
	}
	else
	{
		wait(NULL);
		printf("Succes !\n");
		printf("Some post processing goes here\n");
	}
	
	return (0);
}