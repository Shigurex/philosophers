/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:05:23 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/30 10:26:25 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers_bonus.h"

void	create_process(t_vars *vars)
{
	ssize_t		i;
	t_philos	*philos;

	i = 0;
	while (i < vars->num_philos)
	{
		philos = &vars->philos[i];
		philos->pid = fork();
		if (philos->pid < 0)
			exit(EXIT_FAILURE);
		else if (philos->pid == CHILD)
			exit(printf("hello\n"));
		i++;
	}
}

void	delete_process(t_vars *vars)
{
	ssize_t	i;

	i = 0;
	while (i < vars->num_philos)
	{
		printf("%d\n",waitpid(-1, NULL, 0));
		i++;
	}
	printf("%s, %d\n", __FILE__, __LINE__);
}

void	exec_action(t_vars *vars)
{
	create_process(vars);
	delete_process(vars);
}
