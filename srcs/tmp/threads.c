/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:16:19 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/11 21:17:23 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

void	*thread_func(void *vars)
{
	(void)vars;
}

// void	create_forks(t_vars *vars)
// {
// 	vars->forks = malloc(sizeof(enum e_fork_state) * vars->num_philos);
	
// }

pthread_t	*create_threads(t_vars *vars)
{
	size_t		i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * vars->philos_num);
	i = 0;
	while (i < vars->philos_num)
	{
		pthread_create(&threads[i], NULL, &thread_func, vars);
		i++;
	}
}
